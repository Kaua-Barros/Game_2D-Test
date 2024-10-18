#ifndef __COLLISION_HANDLER_H__
#define __COLLISION_HANDLER_H__

#include "RigidBody.h"
#include "..\TileMap\TileLayer.h"
#include "..\TileMap\GameMap.h"
#include <my-lib/math-vector.h>

using Box = Mylib::Math::Vector<float, 4>;
using Vector = Mylib::Math::Vector<float, 2>;

class CollisionHandler
{
public:
    bool CheckCollision(Box a, Box b);
    void MapCollision(Box box, Vector& position);

    inline static CollisionHandler *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }
    inline int Tilesize() {return m_CollisonLayer->GetTilesize();} 

private:
    CollisionHandler();
    TileMap m_CollisonTileMap;
    TileLayer* m_CollisonLayer;
    static CollisionHandler* s_Instance;
};

#endif //__COLLISION_HANDLER_H__