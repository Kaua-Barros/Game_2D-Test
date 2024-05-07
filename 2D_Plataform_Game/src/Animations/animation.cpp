#include "Animation.h"
#include "..\Graphics\TextureManager.h"

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, float objectWidth, float objectHeigth)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, objectWidth, objectHeigth, m_Width, m_Heigth, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, float spriteWidth, float spriteHeigth, SDL_RendererFlip flip)
{
    m_Width = spriteWidth;
    m_Heigth = spriteHeigth;
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
}
