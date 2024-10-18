#include "Player.h"
#include "../Core/engine.h"
#include <SDL.h>

Player::Player(const Properties &props) : Character(props)
{
    m_TextureID = TextureManager::GetInstance()->Load("../assets/player/red.png");

    m_Collider.SetBuffer((-0.7f * DEFAULT_UNIT_TO_PIXELS * DEFAULT_SCALE),
                         (-1.0f * DEFAULT_UNIT_TO_PIXELS * DEFAULT_SCALE),
                         (1.4f * DEFAULT_UNIT_TO_PIXELS * DEFAULT_SCALE),
                         (1.0f * DEFAULT_UNIT_TO_PIXELS * DEFAULT_SCALE));

    m_RigidBody.SetFriction(0.5f);
    m_RigidBody.ApplyVelocityX(0.0f);
    m_RigidBody.ApplyVelocityY(0.0f);

    m_Direction = Direction_DOWN;
}

Player::~Player()
{
    TextureManager::GetInstance()->CleanTexture();
}

void Player::Draw()
{
    m_Animation.Draw(m_Position.x, m_Position.y, m_Width, m_Height);

    // Desenho da colisão do corpo
    TextureManager::GetInstance()->DrawBox((int)m_Collider.Get().x,
                                           (int)m_Collider.Get().y,
                                           (int)m_Collider.Get().w,
                                           (int)m_Collider.Get().z);
}

void Player::Update(float dt)
{
    Player::Moviment();

    m_RigidBody.Update(dt, m_Position);
    m_Collider.Set(m_Position.x, m_Position.y, m_Width, m_Height);

    m_Origin->x = m_Position.x + (m_Width / 2) * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH;
    m_Origin->y = m_Position.y + (m_Height / 2) * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT;

    CollisionHandler::GetInstance()->MapCollision(m_Collider.Get(), m_Position);

    // Verifica a colisão com todos os inimigos
    for (auto enemy : Engine::GetInstance()->GetEnemies())
    {
        if (CollisionHandler::GetInstance()->CheckCollision(m_Collider.Get(), enemy->GetCollider().Get()))
        {
            std::cout << "Collision with Enemy!" << std::endl;
        }
    }

    // std::cout << "Player position: " << m_Position << std::endl;
    m_Animation.Update();
}

void Player::Moviment()
{
    // Stand By
    if (this->m_Direction == Direction_UP)
    {
        m_Animation.SetProps(m_TextureID, 4, 1, 200, 64, 64);
    }

    if (this->m_Direction == Direction_DOWN)
    {
        m_Animation.SetProps(m_TextureID, 1, 1, 200, 64, 64);
    }

    if (this->m_Direction == Direction_LEFT)
    {
        m_Animation.SetProps(m_TextureID, 2, 1, 200, 64, 64);
    }

    if (this->m_Direction == Direction_RIGHT)
    {
        m_Animation.SetProps(m_TextureID, 3, 1, 200, 64, 64);
    }

    // Animation
    if (Event::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {
        if (!(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_S)))
        {
            m_Direction = Direction_UP;
            m_Animation.SetProps(m_TextureID, 4, 4, 200, 64, 64);
        }
        m_RigidBody.ApplyVelocityY(2.0f * SCALE_HEIGHT * UPWARD);
    }

    if (Event::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
        if (!(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_W)))
        {
            m_Direction = Direction_DOWN;
            m_Animation.SetProps(m_TextureID, 1, 4, 200, 64, 64);
        }
        m_RigidBody.ApplyVelocityY(2.0f * SCALE_HEIGHT * DOWNWARD);
    }

    if (Event::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        if (!(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_D)))
        {
            m_Direction = Direction_LEFT;
            m_Animation.SetProps(m_TextureID, 2, 4, 200, 64, 64);
        }
        m_RigidBody.ApplyVelocityX(2.0f * SCALE_WIDTH * LEFTWARD);
    }

    if (Event::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        if (!(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_A)))
        {
            m_Direction = Direction_RIGHT;
            m_Animation.SetProps(m_TextureID, 3, 4, 200, 64, 64);
        }
        m_RigidBody.ApplyVelocityX(2.0f * SCALE_WIDTH * RIGHTWARD);
    }
}