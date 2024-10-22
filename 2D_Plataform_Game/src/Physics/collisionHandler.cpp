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
std::set<int> intangibleTileIDs = {6, 14, 23, 32, 15};

bool CollisionHandler::MapCollision(Box box, Vector &position)
{
    int tileSizeX = DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH;
    int tileSizeY = DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT;
    int RowCount = m_CollisonLayer->GetRowCount();
    int ColCount = m_CollisonLayer->GetColCount();

    int left_tile = box.x / tileSizeX;
    int right_tile = (box.x + box.w) / tileSizeX;

    int top_tile = box.y / tileSizeY;
    int bottom_tile = (box.y + box.z) / tileSizeY;

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
    float translateX = 0;
    float translateY = 0;
    float finalTranslateX = 0;
    float finalTranslateY = 0;

    float tileX = 0;

    bool isGrounded = false;

    for (int j = top_tile; j <= bottom_tile; ++j)
    {
        for (int i = left_tile; i <= right_tile; ++i)
        {
            int tileID = m_CollisonTileMap[j][i];
            if (tileID > 0 && intangibleTileIDs.find(tileID) == intangibleTileIDs.end())
            {
                translateX = 0;
                translateY = 0;

                tile.x = tileSizeX * i;
                tile.y = tileSizeY * j;

                tile.w = tile.x + tileSizeX;
                tile.z = tile.y + tileSizeY;
                if ((tile.z - 1) >= box.y && (tile.y + 1) <= box.y + box.z && (tile.x + 1) <= box.x + box.w && (tile.w - 1) >= box.x)
                {

                    if (tile.y <= box.y + box.z && tile.z >= box.y)
                    {
                        if (tile.y < (box.y + box.z) && tile.z > (box.y + box.z))
                        {
                            translateY = -((box.y + box.z) - tile.y);
                        }
                        else if (tile.y < box.y && tile.z > box.y)
                        {
                            translateY = -(box.y - tile.z);
                        }
                        else if (tile.y >= box.y && tile.z <= (box.y + box.z / 2))
                        {
                            translateY = tileSizeY;
                        }
                        else if ((tile.y >= (box.y + box.z / 2) && tile.z <= (box.y + box.z)))
                        {
                            translateY = -tileSizeY;
                        }
                    }

                    if (tile.x < box.x + box.w && tile.w > box.x)
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

                    if (std::abs(translateX) > 0 && std::abs(translateY) == 0)
                    {
                        finalTranslateX = translateX;

                        tileX = tile.x;
                    }
                    else if (std::abs(translateY) > 0 && std::abs(translateX) == 0)
                    {
                        finalTranslateY = translateY;
                    }
                    else if (std::abs(translateX) > 0 && std::abs(translateY) > 0)
                    {
                        if (std::abs(translateX) < std::abs(translateY) && j < bottom_tile && j > top_tile)
                        {
                            finalTranslateX = translateX;

                            tileX = tile.x;
                        }
                        if (std::abs(translateX) > std::abs(translateY))
                        {
                            finalTranslateY = translateY;
                        }
                    }
                }
            }
        }
    }

    // std::cout << "Y: " << finalTranslateY << " X: " << finalTranslateX << '\n';

    if (std::abs(finalTranslateY) == std::abs(finalTranslateX))
    {
        position.x += finalTranslateX;
    }
    else if (std::abs(finalTranslateX) > 0)
    {
        position.x += finalTranslateX;
    }
    if (std::abs(finalTranslateX) < std::abs(finalTranslateY) || std::abs(finalTranslateX) == 0)
    {
        position.y += finalTranslateY;
        if (finalTranslateY < 0)
        {
            isGrounded = true;
        }
    }
    return isGrounded;
}
