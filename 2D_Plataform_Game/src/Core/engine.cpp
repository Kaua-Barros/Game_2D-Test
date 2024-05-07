#include "Engine.h"
#include "..\Graphics\TextureManager.h"
#include "..\Inputs\Input.h"
#include "..\Timer\timer.h"
#include "..\Characters\Player.h"
#include "..\TileMap\MapParser.h"
#include <iostream>

Engine *Engine::s_Instance = nullptr;
Player *player = nullptr;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initialize SDL. Error: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("2D Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEEN_WIDTH, SCREEN_HEIGHT, 0);
    if (m_Window == nullptr)
    {
        SDL_Log("Failed to create window. Error: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr)
    {
        SDL_Log("Failed to create Renderer. Error: %s", SDL_GetError());
        return false;
    }

    if (!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to Load Map" << '\n';
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("MAP");

    TextureManager::GetInstance()->Load("player_run", "../assets/Player/Luffy_Run.png");
    TextureManager::GetInstance()->Load("player_StandBy", "../assets/Player/Luffy_StandBy.png");

    player = new Player(Properties(0, 0, 76, 96), "player_StandBy");

    return m_isRunning = true;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    player->Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    m_LevelMap->Render();
    player->Draw();
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
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);

    IMG_Quit();
    SDL_Quit();
    return 0;
}

void Engine::Quit()
{
    m_isRunning = false;
}