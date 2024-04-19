#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "../Object/gameObject.h"
#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

inline constexpr float UNI_MASS = 1.0f;
inline constexpr float GRAVITY = 9.8f;

inline constexpr int FORWARD = 1;
inline constexpr int BACKWARD = -1;

inline constexpr int UPWARD = 1;
inline constexpr int DOWNWARD = -1;

class RigidBody
{
public:
    Vector m_Force;
    RigidBody(){
        m_Mass = UNI_MASS;
        m_Gravity = GRAVITY;
    }

    //Setter Gravity & Mass
    inline void SetMass(float mass) {m_Mass = mass;}
    inline void SetGravity(float gravity) {m_Gravity = gravity;}

    //Force
    inline void ApplyForce(Vector F) {m_Force = F;}
    inline void ApplyForceX(float fX) {m_Force.x = fX;}
    inline void ApplyForceY(float fY) {m_Force.y = fY;}
    inline void UnsetForce() {m_Force.set_zero();}

    //Friction
    inline void ApplyFriction(double Fr) {m_Friction = Fr;}
    inline void UnsetFriction() {m_Friction = 0;}

    //Getters
    inline float GetMass() {return m_Mass;}
    inline Vector Velocity() {return m_Velocity;}
    inline Vector Acceleration() {return m_Acceleration;}

    //Update methode
    void Update(float dt, Vector& position){
        m_Acceleration.x = (m_Force.x * m_Friction)/m_Mass;
        m_Acceleration.y = m_Gravity - m_Force.y/m_Mass;
        m_Velocity = m_Acceleration*dt;
        position += m_Velocity*dt;
    }

    void UpdateX(float dt, Vector& position){
        m_Acceleration.x = (m_Force.x * m_Friction)/m_Mass;
        m_Velocity.x = m_Acceleration.x*dt;
        position.x += m_Velocity.x *dt;
    }

    void UpdateY(float dt, Vector& position){
        m_Acceleration.y = m_Gravity - m_Force.y/m_Mass;
        m_Velocity.y = m_Acceleration.y*dt;
        position.y += m_Velocity.y *dt;
    }

private:
    float m_Gravity;
    float m_Mass;

	Vector m_Velocity;
    Vector m_Acceleration;

    float m_Friction;
};

#endif //__RIGIDBODY_H__