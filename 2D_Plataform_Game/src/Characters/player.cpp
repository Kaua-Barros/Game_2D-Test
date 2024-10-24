#include "Player.h"

Player::Player(const Properties &props) : Character(props)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider.SetBuffer(0, 0, 0, 0);

    m_TextureID = TextureManager::GetInstance()->Load("../assets/Player/Game Boy Advance - One Piece - Monkey D Luffy.png");
    m_Animation_Run.SetProps(TextureManager::GetInstance()->Load("../assets/Player/Luffy_Run.png"), 1, 6, 200, 38, 48);
    m_Animation_Jump.SetProps(m_TextureID, 3, 11, 300, 35, 58);
    m_Animation_StandBy.SetProps(TextureManager::GetInstance()->Load("../assets/Player/Luffy_StandBy.png"), 1, 7, 400, 38, 48);

    m_RigidBody.SetFriction(0.8f);
}

Player::~Player()
{
    TextureManager::GetInstance()->CleanTexture();
}

void Player::Draw()
{
    SDL_Rect Rect{(int)m_Collider.Get().x, (int)m_Collider.Get().y, (int)m_Collider.Get().w, (int)m_Collider.Get().z};
    // SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &Rect);
    m_Animation.Draw(m_Position.x, m_Position.y, m_Size.x, m_Size.y);
}

void Player::Update(float dt)
{
    Player::Moviment(dt);
    m_Origin->x = m_Position.x + (m_Size.x / 2) * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH;
    m_Origin->y = m_Position.y + (m_Size.y / 2) * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT;

    m_RigidBody.UpdateX(dt, m_Position);

    m_RigidBody.UpdateY(dt, m_Position);
    m_Collider.Set(m_Position.x, m_Position.y, m_Size.x, m_Size.y);
    m_IsGrounded = CollisionHandler::GetInstance()->MapCollision(m_Collider.Get(), m_Position);

    m_Animation.Update();
}

void Player::Moviment(float dt)
{
    if (m_IsGrounded)
    {
        m_Animation_StandBy.setFlip(SDL_FLIP_HORIZONTAL);
        m_Animation = m_Animation_StandBy;
    }
    else
    {
        m_Animation_Jump.setFlip(SDL_FLIP_NONE);
        m_Animation = m_Animation_StandBy;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_RigidBody.ApplyVelocityX(1.5f * SCALE_WIDTH * BACKWARD);
        m_Animation_Run.setFlip(SDL_FLIP_NONE);
        m_Animation = m_Animation_Run;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_RigidBody.ApplyVelocityX(1.5f * SCALE_WIDTH * FORWARD);
        m_Animation_Run.setFlip(SDL_FLIP_HORIZONTAL);
        m_Animation = m_Animation_Run;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded)
    {
        if (!playedSound)
        {
            Engine::GetInstance()->PlaySound(0);
            Engine::GetInstance()->SetSoundVolume(0, 128);
            playedSound = true;
        }
        else
        {
            playedSound = false;
        }
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody.ApplyVelocityY(JUMP_FORCE * SCALE_HEIGHT * UPWARD);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        m_RigidBody.ApplyVelocityY(JUMP_FORCE * SCALE_HEIGHT * UPWARD);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_Animation_StandBy.setFlip(SDL_FLIP_HORIZONTAL);
        m_Animation = m_Animation_StandBy;
    }
}