#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "../Object/gameObject.h"
#include "../Global/GlobalProperties.h"

#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

class RigidBody
{
public:
    Vector m_Force;
    RigidBody() = default;

    // Setters
    inline void SetMass(float mass) { m_Mass = mass; }
    inline void SetFriction(float Fr) { m_Friction = Fr; }

    // Force
    inline void ApplyVelocity(Vector V) { m_Velocity += V; }
    inline void ApplyVelocityX(float vX) { m_Velocity.x += vX; }
    inline void ApplyVelocityY(float vY) { m_Velocity.y += vY; }
    inline void UnsetForce() { m_Force.set_zero(); }

    // Getters
    inline float GetMass() { return m_Mass; }
    inline Vector Velocity() { return m_Velocity; }
    inline Vector Force() { return m_Force; }

    // Update methode
    void Update(float dt, Vector &position)
    {
        // Atualiza a velocidade considerando a massa
        m_Velocity.x *= m_Friction / m_Mass;
        position.x += (m_Velocity.x * dt) * (DEFAULT_UNIT_TO_PIXELS);

        m_Velocity.y *= m_Friction / m_Mass;
        position.y += (m_Velocity.y * dt) * (DEFAULT_UNIT_TO_PIXELS);
    }

    void UpdateX(float dt, Vector &position)
    {
        m_Velocity.x *= m_Friction / m_Mass;
        position.x += (m_Velocity.x * dt) * (DEFAULT_UNIT_TO_PIXELS);
    }

    void UpdateY(float dt, Vector &position)
    {
        m_Velocity.y *= m_Friction / m_Mass;
        
    }

private:
    float m_Mass{DEFAULT_MASS};
    float m_Friction{DEFAULT_FRICTION};

    Vector m_Velocity{};
    Vector m_Acceleration{};
};

#endif //__RIGIDBODY_H__