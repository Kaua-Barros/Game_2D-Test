#include "Engine.h"
#include "..\Graphics\TextureManager.h"
#include "..\Inputs\Input.h"
#include "..\Timer\timer.h"
#include "..\Characters\Player.h"
#include "..\TileMap\MapParser.h"
#include "..\Camera\Camera.h"
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

    player = new Player(Properties{.Width = 2, .Heigth = 3, .X = 0, .Y = 0});

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    Camera::GetInstance()->SetLimitPosition(m_LevelMap->GetMapPosition());
    Camera::GetInstance()->SetLimitDimension(m_LevelMap->GetMapDimension());

    return m_isRunning = true;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    player->Update(dt);
    Camera::GetInstance()->Update();
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
    Timer::ReleaseInstance();
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