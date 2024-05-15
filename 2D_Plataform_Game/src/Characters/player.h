#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include "..\Graphics\TextureManager.h"
#include "..\Physics\collisionHandler.h"
#include "..\Inputs\Input.h"
#include "..\Core\Engine.h"
#include "..\Animations\Animation.h"
#include "..\Physics\RigidBody.h"
#include "..\Physics\Collider.h"
#include "my-lib\math-vector.h"
#include <SDL.h>

using Vector = Mylib::Math::Vector<float, 2>;
using Box = Mylib::Math::Vector<float, 4>;

inline constexpr float JUMP_TIME = 20.0f;
inline constexpr float JUMP_FORCE = 9.8f;

#include <string>

class Player : public Character
{
public:
    Player(const Properties &props, std::string TextureID);
    ~Player();

    virtual void Draw() override;
    virtual void Update(float dt) override;
    void Moviment(float dt);

private:
    bool m_IsJumping;
    bool m_IsGrounded;

    float m_JumpTime;
    float m_JumpForce;

    std::string m_TextureID;
    
    Collider* m_Collider;
    Animation* m_Animation;
    RigidBody* m_RigidBody;
    
    Vector m_LastSafePosition;
};

#endif //__PLAYER_H__