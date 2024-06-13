#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "TileLayer.h"
#include <vector>
#include <iostream>

class GameMap
{
public:
  GameMap() = default;

  void Render()
  {
    for (unsigned int i = 0; i < m_MapLayers.size(); i++)
    {
      m_MapLayers[i]->Render();
    }
  }
  void Update()
  {
    for (unsigned int i = 0; i < m_MapLayers.size(); i++)
    {
      m_MapLayers[i]->Update();
    }
  }

  std::vector<Layer*>& GetLayers() { return m_MapLayers; }

private:
  std::vector<Layer*> m_MapLayers;
};

#endif //__GAME_MAP_H__