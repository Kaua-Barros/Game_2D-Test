#include "Animation.h"
#include "..\Graphics\TextureManager.h"

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, float objectWidth, float objectHeight)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, objectWidth, objectHeight, m_Width, m_Height, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::setFlip(SDL_RendererFlip flip){
    m_Flip = flip;
}

void Animation::SetProps(textureID texID, int spriteRow, int frameCount, int animSpeed, float spriteWidth, float spriteHeight)
{
    m_Width = spriteWidth;
    m_Height = spriteHeight;
    m_TextureID = texID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
}
