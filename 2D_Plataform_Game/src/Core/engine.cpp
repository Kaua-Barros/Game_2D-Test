#include "Engine.h"
#include <SDL2/SDL_mixer.h>
#include "..\Graphics\TextureManager.h"
#include "..\Inputs\Input.h"
#include "..\Timer\timer.h"
#include "..\Characters\Player.h"
#include "..\Characters\Enemy.h"
#include "..\TileMap\MapParser.h"
#include "..\Camera\Camera.h"
#include <iostream>

Engine *Engine::s_Instance = nullptr;
Enemy *enemy = nullptr;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initialize SDL. Error: %s", SDL_GetError());
        return false;
    }

    // Inicializa SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("Failed to initialize SDL_mixer. Error: %s", Mix_GetError());
        return false;
    }

    // Preparando as músicas
    std::vector<std::string> musicPaths = {
        "C:/msys64/home/Kaua/SDLtemplate/2D_Plataform_Game/assets/Musics/Onepiece-song.mp3"

        // Adicione mais sons aqui...
    };
    for (const std::string &path : musicPaths)
    {
        if (!LoadMusic(path))
        {
            SDL_Log("Failed to load music: %s", path.c_str());
            return false;
        }
    }

    // Preparando os sons
    std::vector<std::string> soundPaths = {
        "C:/msys64/home/Kaua/SDLtemplate/2D_Plataform_Game/assets/Musics/Jump.mp3"

        // Adicione mais sons aqui...
    };
    for (const std::string &path : soundPaths)
    {
        if (!LoadSound(path))
        {
            SDL_Log("Failed to load sound: %s", path.c_str());
            return false;
        }
    }

    m_Window = SDL_CreateWindow("2D Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (m_Window == nullptr)
    {
        SDL_Log("Failed to create window. Error: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == nullptr)
    {
        SDL_Log("Failed to create Renderer. Error: %s", SDL_GetError());
        return false;
    }

    if (!MapParser::GetInstance()->Load("C:/msys64/home/Kaua/SDLtemplate/2D_Plataform_Game/assets/Map/file.tmx"))
    {
        std::cout << "Failed to Load Map" << '\n';
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("MAP", 0, 0);

    m_Player = new Player(Properties{.Width = 2, .Heigth = 3, .X = 30, .Y = 30});
    enemy = new Enemy(Properties{.Width = 2, .Heigth = 2, .X = 90, .Y = 30});

    Camera::GetInstance()->SetTarget(m_Player->GetOrigin());
    Camera::GetInstance()->SetLimitPosition(m_LevelMap->GetMapPosition());
    Camera::GetInstance()->SetLimitDimension(m_LevelMap->GetMapDimension());

    // Toca a música de fundo
    Engine::GetInstance()->PlayMusic(0);
    SetMusicVolume(70);

    return m_isRunning = true;
}

// Método para carregar musica
bool Engine::LoadMusic(const std::string &path)
{
    Mix_Music *music = Mix_LoadMUS(path.c_str());
    if (music == nullptr)
    {
        SDL_Log("Failed to load music: %s, Error: %s", path.c_str(), Mix_GetError());
        return false;
    }
    m_MusicsList.push_back(music); // Adiciona a musica ao vetor
    return true;
}

// Método para carregar som
bool Engine::LoadSound(const std::string &path)
{
    Mix_Chunk *sound = Mix_LoadWAV(path.c_str());
    if (sound == nullptr)
    {
        SDL_Log("Failed to load sound: %s, Error: %s", path.c_str(), Mix_GetError());
        return false;
    }
    m_SoundsList.push_back(sound); // Adiciona o som ao vetor
    return true;
}

// Método para tocar musica
void Engine::PlayMusic(int musicID)
{
    if (musicID >= 0 && musicID < m_MusicsList.size())
    {
        Mix_PlayMusic(m_MusicsList[musicID], -1);
    }
    else
    {
        SDL_Log("Invalid music ID: %d", musicID);
    }
}

// Método para tocar som
void Engine::PlaySound(int soundID)
{
    if (soundID >= 0 && soundID < m_SoundsList.size())
    {
        Mix_PlayChannel(-1, m_SoundsList[soundID], 0);
    }
    else
    {
        SDL_Log("Invalid sound ID: %d", soundID);
    }
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    m_Player->Update(dt);
    enemy->Update(dt);
    Camera::GetInstance()->Update();
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    m_LevelMap->Render();
    m_Player->Draw();
    enemy->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::CleanGame()
{
    MapParser::GetInstance()->Clean();
    TextureManager::GetInstance()->CleanTexture();
    Timer::ReleaseInstance();

    for (Mix_Music *music : m_MusicsList)
    {
        Mix_FreeMusic(music);
    }
    m_MusicsList.clear();

    for (Mix_Chunk *sound : m_SoundsList)
    {
        Mix_FreeChunk(sound);
    }
    m_SoundsList.clear();

    Mix_CloseAudio();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    IMG_Quit();
    SDL_Quit();
    return 0;
}

void Engine::Quit()
{
    m_isRunning = false;
}

Player *Engine::GetPlayer()
{
    return m_Player;
}
