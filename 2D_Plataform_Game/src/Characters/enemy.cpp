#include "Enemy.h"
#include "..\Core\engine.h"

Enemy::Enemy(const Properties &props) : Character(props)
{
    m_Collider.SetBuffer(0, 0, 0, 0);

    m_TextureID = TextureManager::GetInstance()->Load("../assets/mario.png");
    m_Animation.SetProps(TextureManager::GetInstance()->Load("../assets/mario.png"), 1, 1, 200, 500, 500);

    m_RigidBody.SetFriction(0.8f);
}

Enemy::~Enemy()
{
    TextureManager::GetInstance()->CleanTexture();
}

void Enemy::Draw()
{
    SDL_Rect Rect{(int)m_Collider.Get().x, (int)m_Collider.Get().y, (int)m_Collider.Get().w, (int)m_Collider.Get().z};
    //SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &Rect);
    m_Animation.Draw(m_Position.x, m_Position.y, m_Size.x, m_Size.y);
}

void Enemy::Update(float dt)
{
    Enemy::Moviment(dt);

    m_RigidBody.UpdateX(dt, m_Position);
    m_RigidBody.UpdateY(dt, m_Position);
    m_Collider.Set(m_Position.x, m_Position.y, m_Size.x, m_Size.y);
    CollisionHandler::GetInstance()->MapCollision(m_Collider.Get(), m_Position);
    CollisionPlayer(Engine::GetInstance()->GetPlayer());

    m_Animation.Update();
}

void Enemy::CollisionPlayer(Player *player)
{
    float translateX = 0;
    float translateY = 0;
    Box boxEnemy;
    Box boxPlayer;

    boxPlayer.x = player->getPosition().x;
    boxPlayer.y = player->getPosition().y;
    boxPlayer.w = player->getPosition().x + (player->getSize().x * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH);
    boxPlayer.z = player->getPosition().y + (player->getSize().y * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT);

    boxEnemy.x = m_Position.x;
    boxEnemy.y = m_Position.y;
    boxEnemy.w = m_Position.x + (m_Size.x * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH);
    boxEnemy.z = m_Position.y + (m_Size.y * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT);

    if (boxEnemy.y <= boxPlayer.z && boxEnemy.z >= boxPlayer.y)
    {
        if (boxEnemy.y <= boxPlayer.z && boxEnemy.z >= boxPlayer.z)
        {
            translateY -= (boxPlayer.z - boxEnemy.y);
        }
        else if (boxEnemy.y <= boxPlayer.y && boxEnemy.z >= boxPlayer.y)
        {
            translateY -= (boxPlayer.y - boxEnemy.z);
        }
    }

    if (boxEnemy.x < boxPlayer.w && boxEnemy.w > boxPlayer.x)
    {
        if (boxEnemy.x < boxPlayer.x && boxEnemy.w > boxPlayer.x)
        {
            translateX += -(boxPlayer.x - boxEnemy.w);
        }
        if (boxEnemy.x < boxPlayer.w && boxEnemy.w > boxPlayer.w)
        {
            translateX += (boxEnemy.x - boxPlayer.w);
        }
    }

    std::cout << translateY << " " << translateX << '\n';
    if (std::abs(translateY) > 0 && std::abs(translateX) > 0)
    {

        if (std::abs(translateY) == std::abs(translateX))
        {
            player->getRefPosition().x += translateX / 2.0f;
            m_Position.x -= translateX / 2.0f;
            player->getRefPosition().y += translateY;
        }
        else if (std::abs(translateY) > std::abs(translateX))
        {
            player->getRefPosition().x += translateX / 2.0f;
            m_Position.x -= translateX / 2.0f;
        }
        if (std::abs(translateX) > std::abs(translateY))
        {
            player->getRefPosition().y += translateY;
        }
    }
}

void Enemy::Moviment(float dt)
{
    if (m_WalkTime > WALK_TIME / 2.0f)
    {
        m_WalkTime -= dt;
        m_RigidBody.ApplyVelocityX(0.6f * SCALE_WIDTH * FORWARD);
    }
    else if (m_WalkTime > 0)
    {
        m_WalkTime -= dt;
        m_RigidBody.ApplyVelocityX(0.6f * SCALE_WIDTH * BACKWARD);
    }
    else
    {
        m_WalkTime = WALK_TIME;
    }
}
