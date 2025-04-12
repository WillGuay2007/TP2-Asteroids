#include "Classes.h"

void Game::Initialize()
{
    if (playerShip == nullptr) {
        Vector2 screenCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        playerShip = new Ship(screenCenter, 0.0f, 200.0f, 150.0f);
    } else {
        Vector2 screenCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        playerShip->SetPosition(screenCenter);
    }

    GameInstances.clear();

    SpawnAsteroids(level + 2);

    currentState = PLAYING;

}

void Game::HandlePlayingInput() {

}

void Game::Update() {
    if (currentState == MENU) {
        HandleMenuInput();
    } else if (currentState == PLAYING) {
        HandlePlayingInput();
        for (int i = 0; i < GameInstances.size(); i++) {
            GameInstances[i]->Update(GetFrameTime());
            GameInstances[i]->Draw();
        }
    } else if (currentState == GAME_OVER) {
        HandleGameOverInput();
    }
}
