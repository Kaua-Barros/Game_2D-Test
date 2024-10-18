#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "..\Graphics\TextureManager.h"
#include <string>
#include <SDL.h>

class Animation 
{
public:
    Animation() = default;
    void Update();
    void Draw(float x, float y, float objectWidth, float objectHeigth);
    void SetProps(textureID texID, int spriteRow, int frameCount, int animSpeed, float spriteWidth, float spriteHeigth);

private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimSpeed, m_FrameCount;
    float m_Width, m_Heigth;
    textureID m_TextureID;
};

#endif //__ANIMATION_H__