#include "Event.h"
#include "..\Core\Engine.h"

Event *Event::s_Instance = nullptr;

Event::Event()
{
    m_KeyStates = SDL_GetKeyboardState(NULL);
}

void Event::Listen()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Engine::GetInstance()->Quit();
            break;
        case SDL_KEYDOWN:
            KeyDown();
            break;
        case SDL_KEYUP:
            KeyUp();
            break;
        }
    }
}

bool Event::GetKeyDown(SDL_Scancode key)
{
    return (m_KeyStates[key] == 1);
}

void Event::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Event::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}
