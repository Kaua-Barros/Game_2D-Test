#ifndef __CHARACTER_H__ 
#define __CHARACTER_H__

#include "..\Object\RectObject.h"
#include <string>

class Character : public RectObject
{
public:
    Character(const Properties& props): RectObject(props) {}

protected:
    std::string m_Name;
};

#endif //__CHARACTER_H__