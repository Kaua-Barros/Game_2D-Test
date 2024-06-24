#ifndef GLOBALPROPERTIES_H
#define GLOBALPROPERTIES_H

// Constantes de resolução // 640 x 360 : 854 x 480 : 1024 x 576 : 1280 x 720 : 1366 X 768
inline constexpr int SCREEN_WIDTH = 854;
inline constexpr int SCREEN_HEIGHT = 480;

// Definição de escala padrão
inline constexpr float DEFAULT_SCALE = 1;

// Constantes para conversão de unidades
inline constexpr float SCALE_WIDTH = DEFAULT_SCALE; // X
inline constexpr float SCALE_HEIGHT = DEFAULT_SCALE; // Y
// Constantes para conversão de unidades
inline constexpr float DEFAULT_UNIT_TO_PIXELS = 32.0f;

// Constantes de física padrão
inline constexpr float DEFAULT_MASS = 1.0f;
inline constexpr float DEFAULT_GRAVITY = 9.8f;
inline constexpr float DEFAULT_FRICTION = 0.8f;

#endif // GLOBALPROPERTIES_H
