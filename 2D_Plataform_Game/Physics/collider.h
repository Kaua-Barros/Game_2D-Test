#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL.h"
#include "..\Global\GlobalProperties.h"
#include "my-lib/math-vector.h"

using Box = Mylib::Math::Vector<float, 4>;

class Collider
{
public:
    inline Box Get() { return m_Box; }
    inline void SetBuffer(float x, float y, float w, float h) {
        m_Buffer.x = x;
        m_Buffer.y = y;
        m_Buffer.w = w;
        m_Buffer.z = h;
    };

    void Set(float x, float y, float w, float h){
        m_Box.x = x - m_Buffer.x;
        m_Box.y = y - m_Buffer.y;
        m_Box.w = w * UNIT_TO_PIXELS - m_Buffer.w;
        m_Box.z = h * UNIT_TO_PIXELS - m_Buffer.z;
    }

private:
    Box m_Box;
    Box m_Buffer;
};

#endif //__COLLIDER_H__