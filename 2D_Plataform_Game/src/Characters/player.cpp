#include "Player.h"

Player::Player(const Properties &props, std::string TextureID) : Character(props)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);

    m_TextureID = TextureID;
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_RigidBody->SetFriction(0.8f);
}

Player::~Player()
{
    TextureManager::GetInstance()->CleanTexture();
}

void Player::Draw()
{
    m_Animation->Draw(m_Position.x, m_Position.y, m_Size.x, m_Size.y);

    Box box = m_Collider->Get();
    SDL_Rect SDL_Box {(int)box.x, (int)box.y, (int)box.w, (int)box.z};
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &SDL_Box);
}

void Player::Update(float dt)
{    
    Player::Moviment(dt);

    m_LastSafePosition.x = m_Position.x;
    m_RigidBody->UpdateX(dt, m_Position);
    m_Collider->Set(m_Position.x, m_Position.y, (m_Size.x * DEFAULT_UNIT_TO_PIXELS) - 10, (m_Size.y * DEFAULT_UNIT_TO_PIXELS));

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_Position.x = m_LastSafePosition.x;
    }

    m_LastSafePosition.y = m_Position.y;
    m_RigidBody->UpdateY(dt, m_Position);
    m_Collider->Set(m_Position.x, m_Position.y, (m_Size.x * DEFAULT_UNIT_TO_PIXELS) - 10, (m_Size.y * DEFAULT_UNIT_TO_PIXELS));

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_IsGrounded = true;
        m_Position.y = m_LastSafePosition.y;
    }
    else
    {
        m_IsGrounded = false;
    }

    m_Animation->Update();
}

void Player::Moviment(float dt)
{
    m_Animation->SetProps("player_StandBy", 1, 7, 400, 38, 48, SDL_FLIP_HORIZONTAL);
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_RigidBody->ApplyForceX(2 * BACKWARD);
        m_Animation->SetProps("player_run", 1, 6, 200, 38, 48, SDL_FLIP_NONE);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_RigidBody->ApplyForceX(2 * FORWARD);
        m_Animation->SetProps("player_run", 1, 6, 200, 38, 48, SDL_FLIP_HORIZONTAL);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(JUMP_FORCE * UPWARD);
    }
        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(JUMP_FORCE * UPWARD);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_Animation->SetProps("player_StandBy", 1, 7, 400, 38, 48, SDL_FLIP_HORIZONTAL);
    }
}
