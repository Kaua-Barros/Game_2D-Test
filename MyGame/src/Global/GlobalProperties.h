#ifndef GLOBALPROPERTIES_H
#define GLOBALPROPERTIES_H

// Constantes de resolução // 640 x 360 : 854 x 480 : 1024 x 576 : 1280 x 720 : 1366 X 768
inline constexpr int SCREEN_WIDTH = 1024;
inline constexpr int SCREEN_HEIGHT = 576;

// Definição de escala padrão
inline constexpr float DEFAULT_SCALE = 3;

// Constantes para conversão de unidades
inline constexpr float SCALE_WIDTH = DEFAULT_SCALE;
inline constexpr float SCALE_HEIGHT = DEFAULT_SCALE;
inline constexpr float DEFAULT_UNIT_TO_PIXELS = 16.0f;

// Constantes de física padrão
inline constexpr float DEFAULT_MASS = 1.0f;
inline constexpr float DEFAULT_FRICTION = 0.8f;

// Constantes de direção de movimentação
inline constexpr int UPWARD = -1;
inline constexpr int DOWNWARD = 1;
inline constexpr int RIGHTWARD = 1;
inline constexpr int LEFTWARD = -1;

// Constantes de direção de observação
enum Direction
{
    Direction_UP,
    Direction_DOWN,
    Direction_LEFT,
    Direction_RIGHT
};

#endif // GLOBALPROPERTIES_H