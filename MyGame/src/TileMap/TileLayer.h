#ifndef __TILE_LAYER_H__
#define __TILE_LAYER_H__

#include "../Graphics/textureManager.h"
#include "Layer.h"
#include <string>
#include <vector>

struct Tileset
{
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    std::string Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer
{
public:
    TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets);
    virtual ~TileLayer() = default;

    virtual void Render(const Vector& position);
    virtual void Update();
    inline int GetTilesize() {return m_TileSize;}
    inline TileMap GetTileMap() { return m_TileMap; }
    inline int GetRowCount() { return m_RowCount; }
    inline int GetColCount() { return m_ColCount; }
    inline TilesetList GetTilesetList() { return m_Tilesets; }

private:
    int m_TileSize;
    int m_RowCount, m_ColCount;

    textureID m_TextureID;
    TileMap m_TileMap;
    TilesetList m_Tilesets;
};

#endif // __TILE_LAYER_H__