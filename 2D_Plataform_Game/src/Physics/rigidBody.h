#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "../Object/gameObject.h"
#include "../Global/GlobalProperties.h"

#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

inline constexpr float FORWARD = 1.0f;
inline constexpr float BACKWARD = -1.0f;

inline constexpr float UPWARD = -1.0f;
inline constexpr float DOWNWARD = 1.0f;

const float VELOCITY_Y_MAX = 9.8f * (SCALE_HEIGHT);
const float VELOCITY_Y_MIN = -9.8f * (SCALE_HEIGHT);

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
    inline void ApplyVelocity(Vector V) { m_Velocity += V; }
    inline void ApplyVelocityX(float vX) { m_Velocity.x += vX; }
    inline void ApplyVelocityY(float vY) { m_Velocity.y += vY; }
    inline void UnsetForce() { m_Force.set_zero(); }

    // Getters
    inline float GetMass() { return m_Mass; }
    inline float GetGravity() { return m_Gravity; }
    inline Vector Velocity() { return m_Velocity; }
    inline Vector Force() { return m_Force; }

    // Update methode
    void Update(float dt, Vector &position)
    {
        // Atualiza a velocidade considerando gravidade e massa
        m_Velocity.y = (m_Velocity.y + m_Gravity * m_Mass * dt);
        m_Velocity.x *= m_Friction / m_Mass;

        // Limita a velocidade em Y para o intervalo definido
        if (m_Velocity.y > VELOCITY_Y_MAX)
        {
            m_Velocity.y = VELOCITY_Y_MAX;
        }
        else if (m_Velocity.y < VELOCITY_Y_MIN)
        {
            m_Velocity.y = VELOCITY_Y_MIN;
        }
        position += (m_Velocity * dt) * (DEFAULT_UNIT_TO_PIXELS);
    }

    void UpdateX(float dt, Vector &position)
    {
        m_Velocity.x *= m_Friction / m_Mass;
        position.x += (m_Velocity.x * dt) * (DEFAULT_UNIT_TO_PIXELS);
    }

    void UpdateY(float dt, Vector &position)
    {
        // Atualiza a velocidade considerando gravidade e massa
        m_Velocity.y = (m_Velocity.y + m_Gravity * m_Mass * dt);

        // Limita a velocidade em Y para o intervalo definido
        if (m_Velocity.y > VELOCITY_Y_MAX)
        {
            m_Velocity.y = VELOCITY_Y_MAX;
        }
        else if (m_Velocity.y < VELOCITY_Y_MIN)
        {
            m_Velocity.y = VELOCITY_Y_MIN;
        }

        // Atualiza a posição
        position.y += (m_Velocity.y * dt) * (DEFAULT_UNIT_TO_PIXELS);
    }

private:
    float m_Gravity{DEFAULT_GRAVITY};
    float m_Mass{DEFAULT_MASS};
    float m_Friction{DEFAULT_FRICTION};

    Vector m_Velocity{};
    Vector m_Acceleration{};
};

#endif //__RIGIDBODY_H__