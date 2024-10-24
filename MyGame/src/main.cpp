#include "Core\Engine.h"
#include "Timer\timer.h"

/* 
cd SDLtemplate/MyGame/src

g++ main.cpp Core/Engine.cpp Graphics/TextureManager.cpp Characters/Player.cpp Characters/Enemy.cpp Animations/Animation.cpp Events/Event.cpp Timer/timer.cpp 
TileMap/TileLayer.cpp TileMap/MapParser.cpp Camera/Camera.cpp Physics/collisionHandler.cpp Vendor/TinyXML2/tinyxml2.cpp -o main.exe -std=c++23 -I/ucrt64/include/SDL2 
-I/home/braya/SDLtemplate/MyGame/src/Vendor/my-lib/include -I/home/braya/SDLtemplate/MyGame/src/Vendor/TinyXML2 
-L/home/braya/SDLtemplate/MyGame/src/Vendor/TinyXML2 -Dmain=SDL_main -L/ucrt64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

g++ main.cpp Core/Engine.cpp Graphics/TextureManager.cpp Characters/Player.cpp Characters/Enemy.cpp Animations/Animation.cpp Events/Event.cpp Timer/timer.cpp TileMap/TileLayer.cpp TileMap/MapParser.cpp Camera/Camera.cpp Physics/collisionHandler.cpp Vendor/TinyXML2/tinyxml2.cpp -o main.exe -std=c++23 -I/ucrt64/include/SDL2 -I/home/braya/SDLtemplate/MyGame/src/Vendor/my-lib/include -I/home/braya/SDLtemplate/MyGame/src/Vendor/TinyXML2 -L/home/braya/SDLtemplate/MyGame/src/Vendor/TinyXML2 -Dmain=SDL_main -L/ucrt64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
*/

int main(int argc, char *argv[]){

    Engine::GetInstance()->Init();


    while (Engine::GetInstance()->isRunning()){
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->CleanGame();
    
    return 0;
}