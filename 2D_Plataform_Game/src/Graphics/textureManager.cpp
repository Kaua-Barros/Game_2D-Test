#include "TextureManager.h"
#include "..\Global\GlobalProperties.h"
#include "..\Core\engine.h"
#include "..\Camera\Camera.h"

using Vector = Mylib::Math::Vector<float, 2>;
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
    SDL_Rect srcRect = {0, 0, (int)(width), (int)(height)};

    Vector cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {
        (int)(x - cam.x),
        (int)(y - cam.y),
        (int)((width * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH)),
        (int)((height * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT))};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), *id.it, &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(textureID id, int x, int y, float objectWidth, float objectHeight, float spriteWidth, float spriteHeight, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {
        (int)(spriteWidth * frame),
        (int)(spriteHeight * (row - 1)),
        (int)(spriteWidth),
        (int)(spriteHeight)};

    Vector cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {
        (int)(x - cam.x),
        (int)(y - cam.y),
        (int)((objectWidth * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH)),
        (int)((objectHeight * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT))};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), *id.it, &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(textureID tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};

    Vector cam = Camera::GetInstance()->GetPosition();
    //std::cout << (int)((SCALE_WIDTH)) << " , " << (int)((SCALE_HEIGHT)) << std::endl;
    SDL_Rect dstRect = {
        (int)((x * SCALE_WIDTH - cam.x)),
        (int)((y * SCALE_HEIGHT - cam.y)),
        (int)(((tileSize * SCALE_WIDTH))),
        (int)(((tileSize * SCALE_HEIGHT)))};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), *tilesetID.it, &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Drop(textureID id)
{
    SDL_DestroyTexture(*id.it);
    m_TextureList.erase(id.it);
}

void TextureManager::CleanTexture()
{
    for (auto &texture : m_TextureList)
    {
        SDL_DestroyTexture(texture);
    }
    m_TextureList.clear();
}