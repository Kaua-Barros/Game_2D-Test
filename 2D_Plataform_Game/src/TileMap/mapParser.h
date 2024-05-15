#ifndef __MAP_PARSER_H__
#define __MAP_PARSER_H__

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml2.h"

class MapParser
{
public:
    bool Load();
    void Clean();

    inline GameMap *GetMap(std::string id) { return m_MapDict[id]; }
    inline static MapParser *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

private:
    MapParser() = default;

    bool Parse(std::string id, std::string source);
    Tileset ParseTileset(tinyxml2::XMLElement *xmlTileset);
    TileLayer *ParseTileLayer(tinyxml2::XMLElement *xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

    static MapParser *s_Instance;
    std::map<std::string, GameMap *> m_MapDict;
};

#endif //__MAP_PARSER_H__