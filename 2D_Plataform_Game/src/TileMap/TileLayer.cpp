#include "TileLayer.h"
#include "../Graphics/textureManager.h"
#include <iostream>


TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets)
{
    m_TileSize = tilesize;
    m_RowCount = rowcount;
    m_ColCount = colcount;
    m_TileMap = tilemap;
    m_Tilesets = tilesets;

    for (unsigned int i = 0; i < m_Tilesets.size(); i++)
    {
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "../assets/map/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render()
{
    for (unsigned int i = 0; i < m_RowCount; i++)
    {
        for (unsigned int j = 0; j < m_ColCount; j++)
        {
            int tileID = m_TileMap[i][j];

            if (tileID == 0)
            {
                continue;
            }
            else
            {
                Tileset ts;
                for (unsigned int k = 0; k < m_Tilesets.size(); k++)
                {
                    if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID)
                    {
                        ts = m_Tilesets[k];
                        break;
                    }
                }

                int adjustedTileID = tileID - ts.FirstID; // Ajusta o ID do tile dentro do tileset

                int tileRow = adjustedTileID / ts.ColCount;
                int tileCol = adjustedTileID % ts.ColCount;

                TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileCol);
            }
        }
    }
}


void TileLayer::Update()
{
}
