#include "Enemy.h"
#include "../Core/engine.h"
#include "../Graphics/textureManager.h"
#include <SDL.h>

Enemy::Enemy(const Properties &props) : Character(props)
{
    m_TextureID = TextureManager::GetInstance()->Load("../assets/enemy/green.png");

    m_Collider.SetBuffer(-0.7f * DEFAULT_UNIT_TO_PIXELS * DEFAULT_SCALE,
                         -1.0f * DEFAULT_UNIT_TO_PIXELS * DEFAULT_SCALE,
                         1.4f * DEFAULT_UNIT_TO_PIXELS * DEFAULT_SCALE,
                         1.0f * DEFAULT_UNIT_TO_PIXELS * DEFAULT_SCALE);

    m_RigidBody.SetFriction(0.5f);
    m_RigidBody.ApplyVelocityX(0.0f);
    m_RigidBody.ApplyVelocityY(0.0f);

    m_Direction = Direction_DOWN;
}

Enemy::~Enemy()
{
    TextureManager::GetInstance()->CleanTexture();
}

void Enemy::Draw()
{
    m_Animation.Draw(m_Position.x, m_Position.y, m_Width, m_Height);

    // Desenho da colisão do aggro
    TextureManager::GetInstance()->DrawBox((int)m_AggroArea.Get().x,
                                           (int)m_AggroArea.Get().y,
                                           (int)m_AggroArea.Get().w,
                                           (int)m_AggroArea.Get().z);

    // Desenho da colisão do corpo
    TextureManager::GetInstance()->DrawBox((int)m_Collider.Get().x,
                                           (int)m_Collider.Get().y,
                                           (int)m_Collider.Get().w,
                                           (int)m_Collider.Get().z);
}

void Enemy::Update(float dt)
{
    Vector target = *Engine::GetInstance()->GetPlayer()->GetOrigin();
    Moviment(target);

    m_RigidBody.Update(dt, m_Position);
    m_Collider.Set(m_Position.x, m_Position.y, m_Width, m_Height);
    m_AggroArea.Set(m_Position.x - DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH * 2.5, m_Position.y - SCALE_HEIGHT * DEFAULT_UNIT_TO_PIXELS * 2, 7, 7);

    // Atualização da origem
    m_Origin->x = m_Position.x + (m_Width / 2) * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH;
    m_Origin->y = m_Position.y + (m_Height / 2) * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT;

    CollisionHandler::GetInstance()->MapCollision(m_Collider.Get(), m_Position);
    auto player = Engine::GetInstance()->GetPlayer();
    // Verifique a colisão do Aggro com o enemy
    if (CollisionHandler::GetInstance()->CheckCollision(m_AggroArea.Get(), player->GetCollider().Get()))
    {
        m_IsAggro = true;
        std::cout << "Aggro Collision with Player!" << std::endl;
    }
    else
    {
        m_IsAggro = false;
    }

    // Verifique a colisão do corpo com o enemy
    if (CollisionHandler::GetInstance()->CheckCollision(m_Collider.Get(), player->GetCollider().Get()))
    {
        std::cout << "Body Collision with Player!" << std::endl;
    }

    // std::cout << "Enemy position: " << m_Position << std::endl;
    m_Animation.Update();
}

void Enemy::Moviment(Vector target)
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
    if (target.y < Enemy::GetOrigin()->y - 3.0f && m_IsAggro == true)
    {
        if (!(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_S)))
        {
            m_Direction = Direction_UP;
            m_Animation.SetProps(m_TextureID, 4, 4, 200, 64, 64);
        }
        m_RigidBody.ApplyVelocityY(1.0f * SCALE_HEIGHT * UPWARD);
    }

    if (target.y > Enemy::GetOrigin()->y + 3.0f && m_IsAggro == true)
    {
        if (!(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_W)))
        {
            m_Direction = Direction_DOWN;
            m_Animation.SetProps(m_TextureID, 1, 4, 200, 64, 64);
        }
        m_RigidBody.ApplyVelocityY(1.0f * SCALE_HEIGHT * DOWNWARD);
    }

    if (target.x < Enemy::GetOrigin()->x - 3.0f && m_IsAggro == true)
    {
        if (!(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_D)))
        {
            m_Direction = Direction_LEFT;
            m_Animation.SetProps(m_TextureID, 2, 4, 200, 64, 64);
        }
        m_RigidBody.ApplyVelocityX(1.0f * SCALE_WIDTH * LEFTWARD);
    }

    if (target.x > Enemy::GetOrigin()->x + 3.0f && m_IsAggro == true)
    {
        if (!(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_A)))
        {
            m_Direction = Direction_RIGHT;
            m_Animation.SetProps(m_TextureID, 3, 4, 200, 64, 64);
        }
        m_RigidBody.ApplyVelocityX(1.0f * SCALE_WIDTH * RIGHTWARD);
    }
}
