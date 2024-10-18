#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "..\Core\engine.h"
#include <my-lib/math-vector.h>
#include "SDL.h"

using Vector = Mylib::Math::Vector<float, 2>;

class Camera
{

public:
    void Update(float dt);

    inline SDL_Rect GetViewBox() { return m_ViewBox; }
    inline Vector GetPosition() { return m_Position; }

    inline void SetTarget(Vector *target) { m_Target = target; }
    inline void SetLimitPosition(Vector mapPosition) { m_LimitPosition = mapPosition; }
    inline void SetLimitDimension(Vector mapDimension) { m_LimitDimension = mapDimension; }

    inline static Camera *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

private:
    Camera() { m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; }

    Vector *m_Target;
    Vector m_LimitPosition;
    Vector m_LimitDimension;
    Vector m_Position;

    SDL_Rect m_ViewBox;
    static Camera *s_Instance;
};

#endif // __CAMERA_H__
