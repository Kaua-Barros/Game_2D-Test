#ifndef __LAYER_H__
#define __LAYER_H__

class Layer
{
public:
    virtual void Render() = 0;
    virtual void Update() = 0;
};

#endif // LAYER_H