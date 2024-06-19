#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Global/GlobalProperties.h"

TextureManager *TextureManager::s_Instance = nullptr;

textureID TextureManager::Load(std::string filename)
{
    SDL_Surface *surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Failed to create surface. Error: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        // return false; implementar: error thrw
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface. Error: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        // return false; implementar: error thrw
    }

    textureID ID = {.it = m_TextureList.insert(m_TextureList.end(), texture)};
    SDL_FreeSurface(surface);
    return ID;
}

void TextureManager::Draw(textureID id, int x, int y, float width, float height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, (int)(width * UNIT_TO_PIXELS), (int)(height * UNIT_TO_PIXELS)};
    SDL_Rect dstRect = {(int)(x), (int)(y), (int)(width * UNIT_TO_PIXELS), (int)(height * UNIT_TO_PIXELS)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), *id.it, &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(textureID id, int x, int y, float objectWidth, float objectHeight, float spriteWidth, float spriteHeight, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {(int)((spriteWidth * frame)), (int)((spriteHeight * (row - 1))), (int)(spriteWidth), (int)(spriteHeight)};
    SDL_Rect dstRect = {(int)(x), (int)(y), (int)(objectWidth * UNIT_TO_PIXELS), (int)(objectHeight * UNIT_TO_PIXELS)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), *id.it, &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(textureID tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    int reSize = (UNIT_TO_PIXELS / tileSize);
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
    SDL_Rect dstRect = {x * reSize, y * reSize, tileSize * reSize, tileSize * reSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), *tilesetID.it, &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Drop(textureID id)
{
    SDL_DestroyTexture(*id.it);
    m_TextureList.erase(id.it);
}

void TextureManager::CleanTexture()
{
    for (auto& texture : m_TextureList) {
        SDL_DestroyTexture(texture);
    }
    m_TextureList.clear();
}