#ifndef __IOBJECT_H__
#define __IOBJECT_H__

class IObject
{
public:
    virtual ~IObject() = default;
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
};

#endif // __IOBJECT_H__