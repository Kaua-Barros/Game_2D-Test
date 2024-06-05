#include "CollisionHandler.h"
#include "..\Core\Engine.h"
#include "..\Global\GlobalProperties.h"

CollisionHandler *CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    auto layers = Engine::GetInstance()->GetMap()->GetLayers();
    if (!layers.empty())
    {
        m_CollisonLayer = (TileLayer *)layers.back();
    }
    else
    {
        m_CollisonLayer = nullptr;
    }
    if (m_CollisonLayer != nullptr)
    {
        m_CollisonTileMap = m_CollisonLayer->GetTileMap();
    }
    else
    {
        m_CollisonTileMap = {};
    }
}

#include <set>

// Adicione a lista de IDs de tiles intangíveis
std::set<int> intangibleTileIDs = {1};

bool CollisionHandler::MapCollision(Box box)
{
    int tileSize = 1 * UNIT_TO_PIXELS;
    int RowCount = m_CollisonLayer->GetRowCount();
    int ColCount = m_CollisonLayer->GetColCount();

    int left_tile = box.x / tileSize;
    int right_tile = (box.x + box.w) / tileSize;

    int top_tile = box.y / tileSize;
    int bottom_tile = (box.y + box.z) / tileSize;

    if (left_tile < 0)
    {
        left_tile = 0;
    }
    if (right_tile > ColCount)
    {
        right_tile = ColCount;
    }

    if (top_tile < 0)
    {
        top_tile = 0;
    }
    if (bottom_tile > RowCount)
    {
        bottom_tile = RowCount;
    }

    for (int i = left_tile; i <= right_tile; ++i)
    {
        for (int j = top_tile; j <= bottom_tile; ++j)
        {
            int tileID = m_CollisonTileMap[j][i];
            if (tileID > 0 && intangibleTileIDs.find(tileID) == intangibleTileIDs.end())
            {
                return true;
            }
        }
    }
    return false;
}


void CollisionHandler::ApplyCollisionForce(Box box, RigidBody &rigidBody, bool &isGrounded)
{
    // Convertendo as dimensões para pixel

    Box rightBox;
    rightBox.x = box.x + box.w + (box.w / 12 - box.w / 2);
    rightBox.y = box.y + box.z / 10;
    rightBox.w = box.w / 2;
    rightBox.z = box.z - (2 * box.z / 10);

    Box leftBox;
    leftBox.x = box.x - box.w / 12;
    leftBox.y = box.y + box.z / 10;
    leftBox.w = box.w / 2;
    leftBox.z = box.z - (2 * box.z / 10);

    Box belowBox;
    belowBox.x = box.x;
    belowBox.y = box.y + box.z/2;
    belowBox.w = box.w;
    belowBox.z = box.z / 2;

    Box upwardBox;
    upwardBox.x = box.x;
    upwardBox.y = box.y;
    upwardBox.w = box.w;
    upwardBox.z = box.z / 2;

    // Verifica a colisão no eixo y
    float force;
    if (MapCollision(belowBox))
    {
        std::cout << "baixo?" << '\n';
        std::cout << rigidBody.Force().y << '\n';
        isGrounded = true;
        rigidBody.ApplyForceY(rigidBody.Force().y * -1 - (rigidBody.GetGravity() * rigidBody.GetMass())); // Aplica força para cima
    }
    else if (MapCollision(upwardBox))
    {
        std::cout << "cima?" << '\n';
        std::cout << rigidBody.Force().y << '\n';
        isGrounded = false;
        rigidBody.ApplyForceY(rigidBody.Force().y * -1 + (rigidBody.GetGravity() * rigidBody.GetMass())); // Aplica força para cima
    }
    if (MapCollision(rightBox))
    {
        std::cout << "Direita?" << '\n';
        std::cout << rigidBody.Force().x << '\n';
        rigidBody.ApplyForceX(-std::abs(rigidBody.Force().x + 5)); // Aplica força para a esquerda
    }
    else if (MapCollision(leftBox))
    {
        std::cout << "Esquerda?" << '\n';
        std::cout << rigidBody.Force().x << '\n';
        rigidBody.ApplyForceX(std::abs(rigidBody.Force().x) + 5); // Aplica força para a direita
    }
}
