#ifndef __TIMER_H__ 
#define __TIMER_H__

#include "SDL.h"

const float FPS = 60.0f;
const float FRAME_TIME = 1.0f / FPS;

class Timer
{
public:
    void Tick();
    float GetDeltaTime() { return m_DeltaTime; }
    static Timer *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }
    static void ReleaseInstance();

    inline float GetTime()
    {
        return static_cast<float>(SDL_GetTicks()) / 1000.0f;
    }

private:
    Timer() = default;
    ~Timer() = default;
    static Timer *s_Instance;
    float m_DeltaTime;
    float m_LastTime = 0;
};

#endif //__TIMER_H__