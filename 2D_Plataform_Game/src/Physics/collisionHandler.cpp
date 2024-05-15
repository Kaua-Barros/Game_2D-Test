#include "CollisionHandler.h"
#include "..\Core\Engine.h"
#include "..\Global\GlobalProperties.h"

CollisionHandler *CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    auto layers = Engine::GetInstance()->GetMap()->GetLayers();
    if (!layers.empty()) {
        m_CollisonLayer = (TileLayer *)layers.back();
    } else {
        m_CollisonLayer = nullptr;
    }
    m_CollisonTileMap = m_CollisonLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(Box object1, Box object2)
{
    bool x_overlaps = (object1.x < object2.x + object2.w) && (object1.x + object1.w > object2.x);
    bool y_overlaps = (object1.y < object2.y + object2.z) && (object1.y + object1.z > object2.y);
    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(Box box)
{
    int tileSize = 1 * DEFAULT_UNIT_TO_PIXELS;
    int RowCount = 20;
    int ColCount = 60;

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
            if (m_CollisonTileMap[j][i] > 0)
            {
                return true;
            }
        }
    }
    return false;
}

void CollisionHandler::ApplyCollisionForce(Vector &positionObject1, Vector sizeObject1, RigidBody *rigidBody, Vector positionObject2, Vector sizeObject2)
{
}
