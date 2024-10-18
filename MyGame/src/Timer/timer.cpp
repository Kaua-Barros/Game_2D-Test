#include "Timer.h"

Timer *Timer::s_Instance = nullptr;

void Timer::Tick()
{
    const auto t = GetTime();
    m_DeltaTime = t - m_LastTime;
    m_LastTime = t;

    if (m_DeltaTime < FRAME_TIME)
    {
        SDL_Delay(static_cast<Uint32>((FRAME_TIME - m_DeltaTime) * 1000.0f));
        m_DeltaTime = FRAME_TIME;
    }
}

void Timer::ReleaseInstance()
{
    delete s_Instance;
    s_Instance = nullptr;
}