#ifndef __TIMER_H__
#define __TIMER_H__

const int FPS = 60;

class Timer
{
public:
    void Tick();
    float GetDeltaTime() {return m_DeltaTime;}
    static Timer* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new Timer();}
private:
    Timer() = default;
    static Timer* s_Instance;
    float m_DeltaTime;
    float m_LastTime;
};

#endif //__TIMER_H__