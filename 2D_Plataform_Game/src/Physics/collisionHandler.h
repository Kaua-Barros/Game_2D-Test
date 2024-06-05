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
    bool CheckCollision(Box object1, Box object2);
    bool MapCollision(Box box);

    void ApplyCollisionForce(Box box, RigidBody &rigidBody, bool &isGrounded);
    inline static CollisionHandler *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

private:
    CollisionHandler();
    TileMap m_CollisonTileMap;
    TileLayer* m_CollisonLayer;
    static CollisionHandler* s_Instance;
};

#endif //__COLLISION_HANDLER_H__