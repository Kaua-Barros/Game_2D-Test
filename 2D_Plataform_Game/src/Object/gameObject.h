#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#pragma once

#include "IObject.h"

#include <SDL.h>
#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

class GameObject : public IObject
{
public:
    Vector getPosition() const { return m_Position; }
    virtual ~GameObject() override = default;

protected:
    Vector m_Position;
};

#endif // __GAME_OBJECT_H__