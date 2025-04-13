#include "entrypoint.h"
#include "Classes.h"
#include <raylib.h>

Game* game = nullptr;

void raylib_start(void){
    InitWindow(WIDTH, HEIGHT, "ASTEROIDS");
    SetTargetFPS(60);

    game = new Game(3, 0);

    game->Initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        game->Update();
        game->Draw();
        
        EndDrawing();
    }

    delete game;
    CloseWindow();
}