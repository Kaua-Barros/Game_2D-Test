#ifndef __INPUT_H__
#define __INPUT_H__

#include "SDL.h"

class Input 
{
public:
        static Input* GetInstance(){
        return s_Instance = (s_Instance != nullptr)? s_Instance : new Input();
    }
    void Listen();
    bool GetKeyDown(SDL_Scancode key);

private:
    Input();
    void KeyUp();
    void KeyDown();

    const Uint8* m_KeyStates;
    static Input* s_Instance;
};
#endif // __INPUT_H__