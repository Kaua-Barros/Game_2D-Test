#include "MapParser.h"
#include <iostream>

MapParser *MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
    return Parse("MAP", "../assets/Map/file.tmx");
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
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error())
    {
        std::cout << "Failed to load" << source << '\n';
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;

    root->Attribute("height", &rowcount);
    root->Attribute("width", &colcount);
    root->Attribute("tilewidth", &tilesize);

    // Parse Tile sets
    TilesetList tilesets;
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }
    std::cout << tilesets.size() << '\n';

    GameMap* gamemap = new GameMap();

    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
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

Tileset MapParser::ParseTileset(TiXmlElement *xmlTileset)
{
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement *image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer *MapParser::ParseTileLayer(TiXmlElement *xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement *data;
    for (TiXmlElement *e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
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
