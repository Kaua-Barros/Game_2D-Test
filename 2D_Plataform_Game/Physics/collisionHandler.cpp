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

bool CollisionHandler::MapCollision(Box box, Vector &position)
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

    Box tile;
    int translateX = 0;
    int translateY = 0;
    bool isGrounded = false;

    for (int j = top_tile; j <= bottom_tile; ++j)
    {
        for (int i = left_tile; i <= right_tile; ++i)
        {
            int tileID = m_CollisonTileMap[j][i];
            if (tileID > 0 && intangibleTileIDs.find(tileID) == intangibleTileIDs.end())
            {
                translateY = 0;
                translateX = 0;

                tile.x = tileSize * i;
                tile.y = tileSize * j;

                tile.w = tile.x + tileSize;
                tile.z = tile.y + tileSize;

                if (tile.y < box.y + box.z && tile.z > box.y)
                {
                    if (tile.y < (box.y + box.z) && tile.z > (box.y + box.z))
                    {
                        translateY += -((box.y + box.z) - tile.y);
                        isGrounded = true;
                    }
                    else if (tile.y < box.y && tile.z > box.y)
                    {
                        translateY += -(box.y - tile.z);
                    }
                    box.y += translateY;
                }

                if (tile.x < box.x + box.w && tile.w > box.x && j < bottom_tile && j > top_tile)
                {
                    if (tile.x < box.x && tile.w > box.x)
                    {
                        translateX += -(box.x - tile.w);
                    }
                    if (tile.x < (box.x + box.w) && tile.w > (box.x + box.w))
                    {
                        translateX += (tile.x - (box.x + box.w));
                    }
                }

                if (translateX != 0 || translateY != 0)
                {
                    if (std::abs(translateX) > 0)
                    {
                        position.x += translateX;
                        position.y += translateY;
                    }
                    else
                    {
                        position.y += translateY;
                    }
                }
            }
        }
    }
    return isGrounded;
}
