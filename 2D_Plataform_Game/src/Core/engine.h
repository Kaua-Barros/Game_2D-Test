#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL.h>
#include <SDL_mixer.h> 
#include <SDL_image.h>
#include "..\TileMap\GameMap.h"
#include "..\Global\GlobalProperties.h"

class Player; // Forward declaration

class Engine
{
public:
    static Engine *GetInstance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
    }

    bool Init();
    bool CleanGame();
    void Quit();

    void Update();
    void Render();
    void Events();

    Player* GetPlayer();
    inline GameMap *GetMap() { return m_LevelMap; }
    inline bool isRunning() { return m_isRunning; }
    inline SDL_Renderer *GetRenderer() { return m_Renderer; }

    // Métodos para lidar com música
    bool LoadMusic(const std::string& path); // Carrega uma musica no vetor
    void SetMusicVolume(int volume) { Mix_VolumeMusic(volume); }// volume deve estar entre 0 e 128

    void PlayMusic(int musicID); // Toca uma musica pelo índice no vetor
    void StopBackgroundMusic() { Mix_HaltMusic(); }

    // Métodos para lidar com áudio
    bool LoadSound(const std::string& path);  // Carrega um som no vetor
    void PlaySound(int soundID);  // Toca um som pelo índice no vetor
    void SetSoundVolume(int soundID, int volume) { Mix_VolumeChunk(m_SoundsList[soundID], volume); }// volume deve estar entre 0 e 128


private:
    Engine() = default;
    bool m_isRunning;

    Player *m_Player;
    GameMap *m_LevelMap;
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
    static Engine *s_Instance;

    std::vector<Mix_Chunk*> m_SoundsList;
    std::vector<Mix_Music*> m_MusicsList;
};

#endif // __ENGINE_H__