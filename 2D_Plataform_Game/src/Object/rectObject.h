#ifndef __RECT_OBJECT_H__
#define __RECT_OBJECT_H__

#include "gameObject.h"

struct Properties
{
    float Width, Heigth;
    float X, Y;
};

class RectObject : public GameObject
{
public:

    Vector getSize() const { return m_Size; }

    virtual ~RectObject() override = default;
    RectObject(const Properties &props)
    {
        m_Size.x = props.Width;
        m_Size.y = props.Heigth;
        m_Position.x = props.X;
        m_Position.y = props.Y;
    }

protected:
    Vector m_Size;
};
#endif // __RECT_OBJECT_H__