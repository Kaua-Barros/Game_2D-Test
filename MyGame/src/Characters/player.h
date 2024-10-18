#ifndef __PLAYER_H__
#define __PLAYER_H__

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

class Player : public Character
{
public:
    Player(const Properties &props);
    ~Player();

    virtual void Draw();
    virtual void Update(float dt);
    void Moviment();

    Collider &GetCollider() { return m_Collider; }

private:
    textureID m_TextureID;
    Direction m_Direction;
    Animation m_Animation;
    RigidBody m_RigidBody;
    Collider m_Collider;
};

#endif //__PLAYER_H__