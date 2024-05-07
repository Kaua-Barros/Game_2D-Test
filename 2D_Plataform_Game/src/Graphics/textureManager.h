#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <SDL.h>
#include <string>
#include <map>

class TextureManager
{
public:
    std::map<std::string, SDL_Texture *> m_TextureMap;

public:
    static TextureManager *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }
    ~TextureManager();

    bool Load(std::string id, std::string filename);
    void Drop(std::string id);

    void Draw(std::string id, int x, int y, float width, float heigth, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(std::string id, int x, int y, float objectWidth, float objectHeigth, float spriteWidth, float spriteHeigth, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void CleanTexture();

private:
    TextureManager() = default;
    static TextureManager *s_Instance;
};

#endif // __TEXTURE_MANAGER_H__