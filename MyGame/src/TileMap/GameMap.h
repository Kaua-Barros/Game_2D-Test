#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "TileLayer.h"
#include <vector>
#include <iostream>
#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

class GameMap
{
public:
  GameMap() = default;

  void Render()
  {
    for (unsigned int i = 0; i < m_MapLayers.size(); i++)
    {
      m_MapLayers[i]->Render(m_MapPosition);
    }
  }
  // void Update()
  // {
  //   for (unsigned int i = 0; i < m_MapLayers.size(); i++)
  //   {
  //     m_MapLayers[i]->Update();
  //   }
  // }

  std::vector<Layer *> &GetLayers() { return m_MapLayers; }

  void SetMapPosition(float x, float y) { m_MapPosition = Vector(x, y); }
  inline Vector GetMapPosition() { return m_MapPosition; }
  
  void SetMapDimension(float width, float height) { m_MapDimension = Vector(width, height); }
  inline Vector GetMapDimension() { return m_MapDimension; }


private:
  std::vector<Layer *> m_MapLayers;
  Vector m_MapDimension;
  Vector m_MapPosition;
  int m_Width, m_Height;
};

#endif //__GAME_MAP_H__