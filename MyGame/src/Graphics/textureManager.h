#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <SDL.h>
#include <string>
#include <list>
#include <string_view>

struct textureID
{
    std::list<SDL_Texture *>::iterator it;
};

class TextureManager
{
public:
    std::list<SDL_Texture *> m_TextureList;

public:
    static TextureManager *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }
    ~TextureManager();

    textureID Load(std::string filename);
    void Drop(textureID id);

    void Draw(textureID id, int x, int y, float width, float height, SDL_RendererFlip flip);
    void DrawBox(int x, int y, float width, float height);
    void DrawTile(textureID tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(textureID id, int x, int y, float objectWidth, float objectHeight, float spriteWidth, float spriteHeight, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void CleanTexture();

private:
    TextureManager(){};
    static TextureManager *s_Instance;
};

#endif // __TEXTURE_MANAGER_H__