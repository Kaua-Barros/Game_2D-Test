#include "MapParser.h"
#include <sstream>
#include <iostream>

MapParser *MapParser::s_Instance = nullptr;

bool MapParser::Load(const std::string& tmxFilePath)
{
    return Parse("MAP", tmxFilePath);
}

void MapParser::Clean()
{
    for (auto &[_, mapPtr] : m_MapDict)
    {
        mapPtr = nullptr; // Define o ponteiro armazenado no mapa como nullptr
    }

    m_MapDict.clear(); // Limpa o mapa
}

bool MapParser::Parse(std::string id, std::string source)
{
    tinyxml2::XMLDocument xml;
    xml.LoadFile(source.c_str());

    if (xml.Error())
    {
        std::cout << "Failed to load" << source << '\n';
        return false;
    }

    tinyxml2::XMLElement *root = xml.RootElement();
    int rowcount = 0;
    int colcount = 0;
    int tilesize = 0;
    
    rowcount = root->IntAttribute("height", rowcount);
    colcount = root->IntAttribute("width", colcount);
    tilesize = root->IntAttribute("tilewidth", tilesize);

    // Parse Tile sets
    TilesetList tilesets;
    for (tinyxml2::XMLElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    GameMap* gamemap = new GameMap();
    gamemap->SetMapDimension(colcount, rowcount);

    for (tinyxml2::XMLElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer *tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->GetLayers().push_back(tilelayer);
        }
    }

    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(tinyxml2::XMLElement *xmlTileset)
{
    Tileset tileset;
    // tileset.Name = xmlTileset->Attribute("name");
    tileset.FirstID = xmlTileset->IntAttribute("firstgid", tileset.FirstID);

    tileset.TileCount = xmlTileset->IntAttribute("tilecount", tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    tileset.ColCount = xmlTileset->IntAttribute("columns", tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    tileset.TileSize = xmlTileset->IntAttribute("tilewidth", tileset.TileSize);

    tinyxml2::XMLElement *image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer *MapParser::ParseTileLayer(tinyxml2::XMLElement *xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
    tinyxml2::XMLElement *data;
    for (tinyxml2::XMLElement *e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int> (colcount, 0));
    for (int row = 0; row < rowcount; row++)
    {
        for (int col = 0; col < colcount; col++)
        {
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good())
            {
                break;
            }
        }
    }

    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}