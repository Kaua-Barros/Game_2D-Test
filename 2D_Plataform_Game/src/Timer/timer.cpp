#include "Timer.h"
#include "SDL.h"

Timer *Timer::s_Instance = nullptr;

void Timer::Tick()
{
    m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (FPS/1000.0f);
    m_LastTime = SDL_GetTicks();
}
