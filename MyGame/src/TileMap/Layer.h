#ifndef __LAYER_H__
#define __LAYER_H__

#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

class Layer
{
public:
    virtual void Render(const Vector& position) = 0;
    virtual void Update() = 0;
};

#endif // LAYER_H