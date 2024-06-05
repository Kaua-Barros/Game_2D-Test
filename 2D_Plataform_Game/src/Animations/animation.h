#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "..\Graphics\TextureManager.h"
#include <string>
#include <SDL.h>

class Animation 
{
public:
    Animation() = default;
    void SetProps(textureID texID, int spriteRow, int frameCount, int animSpeed, float spriteWidth, float spriteHeight);
    void Update();
    void setFlip(SDL_RendererFlip m_Flip);
    void Draw(float x, float y, float objectWidth, float objectHeight);

private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimSpeed, m_FrameCount;
    float m_Width, m_Height;
    textureID m_TextureID;
    SDL_RendererFlip m_Flip {SDL_FLIP_NONE};
};

#endif //__ANIMATION_H__