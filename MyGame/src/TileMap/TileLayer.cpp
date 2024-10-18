#include "TileLayer.h"
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
        m_TextureID = TextureManager::GetInstance()->Load("../assets/maps/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render(const Vector& position)
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
                
                // Ajusta a posição do desenho pela posição do mapa
                int drawX = j * ts.TileSize;// + position[0];
                int drawY = i * ts.TileSize;// + position[1];
                TextureManager::GetInstance()->DrawTile(m_TextureID, ts.TileSize, drawX, drawY, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::Update()
{
}
