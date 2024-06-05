#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "../Object/gameObject.h"
#include "../Global/GlobalProperties.h"

#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

inline constexpr int FORWARD = 1;
inline constexpr int BACKWARD = -1;

inline constexpr int UPWARD = -1;
inline constexpr int DOWNWARD = 1;

class RigidBody
{
public:
    Vector m_Force;
    RigidBody() = default;

    // Setters
    inline void SetMass(float mass) { m_Mass = mass; }
    inline void SetGravity(float gravity) { m_Gravity = gravity; }
    inline void SetFriction(float Fr) { m_Friction = Fr; }

    // Force
    inline void ApplyForce(Vector F) { m_Force += F; }
    inline void ApplyForceX(float fX) { m_Force.x += fX; }
    inline void ApplyForceY(float fY) { m_Force.y += fY; }
    inline void UnsetForce() { m_Force.set_zero(); }

    // Getters
    inline float GetMass() { return m_Mass; }
    inline float GetGravity() { return m_Gravity; }
    inline Vector Velocity() { return m_Velocity; }
    inline Vector Force() { return m_Force; }

    // Update methode
    void Update(float dt, Vector &position)
    {
        if (dt > 3)
        {
            dt = 1;
        }
        m_Acceleration.x = (m_Force.x * m_Friction) / m_Mass;
        m_Acceleration.y = m_Gravity - m_Force.y / m_Mass;
        m_Velocity = m_Acceleration * dt;
        position += (m_Velocity * dt) * (UNIT_TO_PIXELS/32);
        m_Force = m_Velocity;
    }

    void UpdateX(float dt, Vector &position)
    {
        if (dt > 3)
        {
            dt = 1;
        }
        m_Acceleration.x = (m_Force.x * m_Friction) / m_Mass;
        m_Velocity.x = m_Acceleration.x * dt;
        position.x += (m_Velocity.x * dt) * (UNIT_TO_PIXELS/32);
        m_Force.x = m_Velocity.x;
    }

    void UpdateY(float dt, Vector &position)
    {
        if (dt > 3)
        {
            dt = 1;
        }
        m_Acceleration.y = m_Force.y + (m_Gravity * m_Mass);
        m_Velocity.y = m_Acceleration.y * dt;
        position.y += (m_Velocity.y * dt) * (UNIT_TO_PIXELS/32);
        if (m_Force.y < 0)
        {
            m_Force.y = m_Acceleration.y;
        }
        else
        {
            m_Force.y = 0;
        }
    }

private:
    float m_Gravity{DEFAULT_GRAVITY};
    float m_Mass{DEFAULT_MASS};
    float m_Friction{DEFAULT_FRICTION};

    Vector m_Velocity{};
    Vector m_Acceleration{};
};

#endif //__RIGIDBODY_H__