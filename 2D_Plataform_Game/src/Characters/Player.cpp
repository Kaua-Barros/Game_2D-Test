#include "Player.h"
#include "..\Graphics\TextureManager.h"
#include "..\Inputs\Input.h"
#include <SDL.h>

Player::Player(const Properties& props, std::string TextureID) : Character(props)
{
    m_TextureID = TextureID;
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_RigidBody->ApplyFriction(0.8);
    m_RigidBody->ApplyForceX(0);
    m_RigidBody->ApplyForceY(0);
}

Player::~Player(){
    TextureManager::GetInstance()->CleanTexture();
}

void Player::Draw()
{
    m_Animation->Draw(m_Position.x, m_Position.y, m_Width, m_Height);
}

void Player::Update(float dt)
{
    m_RigidBody->ApplyForceX(m_RigidBody->Acceleration().x);
    Player::Moviment();
    m_RigidBody->UpdateX(dt, m_Position);
    //m_RigidBody->UpdateY(dt, m_Position);

    m_Animation->Update();
}

void Player::Moviment()
{
    m_Animation->SetProps("player_StandBy", 1, 7, 400, 38, 48, SDL_FLIP_HORIZONTAL);
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_RigidBody->ApplyForceX(m_RigidBody->m_Force.x + (2 * BACKWARD));
        m_Animation->SetProps("player_run", 1, 6, 200, 38, 48, SDL_FLIP_NONE);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_RigidBody->ApplyForceX(m_RigidBody->m_Force.x + (2 * FORWARD));
        m_Animation->SetProps("player_run", 1, 6, 200, 38, 48, SDL_FLIP_HORIZONTAL);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {
        m_RigidBody->ApplyForceY(7 * UPWARD);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_Animation->SetProps("player_StandBy", 1, 7, 400, 38, 48, SDL_FLIP_HORIZONTAL);
    }
}
