#ifndef __CHARACTER_H__ 
#define __CHARACTER_H__

#include "..\Object\GameObject.h"
#include <string>

class Character : public GameObject
{
public:
    Character(const Properties& props): GameObject(props) {}
    //Character(const Properties& props): GameObject(props) = default; Não funcionou

protected:
    std::string m_Name;
};

#endif //__CHARACTER_H__