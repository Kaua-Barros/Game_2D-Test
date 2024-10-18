#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"
#include "..\Graphics\TextureManager.h"
#include "..\Characters\Player.h"
#include "..\Physics\collisionHandler.h"
#include "..\Physics\collider.h"
#include "..\Animations\Animation.h"
#include "..\Physics\RigidBody.h"
#include "..\Core\Engine.h"
#include "my-lib\math-vector.h"
#include <SDL.h>

using Vector = Mylib::Math::Vector<float, 2>;
using Box = Mylib::Math::Vector<float, 4>;

#include <string>

inline constexpr float WALK_TIME = 5.00f;

class Enemy : public Character
{
public:
    Enemy(const Properties &props);
    ~Enemy();

    virtual void Draw() override;
    virtual void Update(float dt) override;
    void Moviment(float dt);
    void CollisionPlayer(Player *player);

private:
    float m_WalkTime;

    textureID m_TextureID;

    Collider m_Collider;

    Animation m_Animation;

    RigidBody m_RigidBody;
};

#endif //__ENEMY_H__