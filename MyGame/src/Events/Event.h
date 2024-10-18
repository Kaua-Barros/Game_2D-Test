#ifndef __EVENT_H__
#define __EVENT_H__

#include "SDL.h"

class Event 
{
public:
        static Event* GetInstance(){
        return s_Instance = (s_Instance != nullptr)? s_Instance : new Event();
    }
    void Listen();
    bool GetKeyDown(SDL_Scancode key);

private:
    Event();
    void KeyUp();
    void KeyDown();

    const Uint8* m_KeyStates;
    static Event* s_Instance;
};
#endif // __EVENT_H__