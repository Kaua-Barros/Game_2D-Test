#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"
#include "..\Graphics\TextureManager.h"
#include "..\Animations\Animation.h"
#include "..\Physics\collisionHandler.h"
#include "..\Physics\collider.h"
#include "..\Physics\RigidBody.h"
#include "..\Events\Event.h"
#include <string>
#include "my-lib\math-vector.h"

using Vector = Mylib::Math::Vector<float, 2>;
using Box = Mylib::Math::Vector<float, 4>;

class Enemy : public Character
{
public:
    Enemy(const Properties &props);
    ~Enemy();

    virtual void Draw();
    virtual void Update(float dt);
    void Moviment(Vector target);

    Collider &GetCollider() { return m_Collider; }
    Collider &GetAggroCollider() { return m_AggroArea; }

private:
    textureID m_TextureID;
    Direction m_Direction;
    Animation m_Animation;
    RigidBody m_RigidBody;
    Collider m_Collider;
    Collider m_AggroArea;
    bool m_IsAggro;
};

#endif //__ENEMY_H__