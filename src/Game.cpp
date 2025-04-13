#include "Classes.h"

void Game::AddGameObject(GameObject* obj) {
    GameInstances.push_back(obj);
}

void Game::SpawnAsteroids(int count) {
    for (int i = 0; i < count; i++) {
        Vector2 a_Position;
        a_Position.x = GetRandomValue(50, WIDTH - 50);
        a_Position.y = GetRandomValue(50, HEIGHT - 50);
        while (abs(playerShip->GetPosition().x - a_Position.x) < 100 || abs(playerShip->GetPosition().y - a_Position.y) < 100) {
            a_Position.x = GetRandomValue(50, WIDTH - 50);
            a_Position.y = GetRandomValue(50, HEIGHT - 50);
        }

        int size = GetRandomValue(1, 3);
        float speed = 50.0f + (3 - size) * 25.0f; // +petit = +vite
        
        Asteroid* asteroid = new Asteroid(a_Position, size, speed);
        AddGameObject(asteroid);
    }
}

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
    if (IsKeyPressed(KEY_A)) {
        //playerShip->Rotate(15);
    }
    if (IsKeyPressed(KEY_D)) {
        //playerShip->Rotate(-15);
    }
    if (IsKeyPressed(KEY_SPACE)) {
        //playerShip->Shoot();
    }
    if (IsKeyPressed(KEY_S)) {
        //Ralentir
    }
    if (IsKeyPressed(KEY_W)) {
        //Thrust
    }
}

void Game::Update() {
    if (currentState == MENU) {
        //HandleMenuInput();
    } 
    
    else if (currentState == PLAYING) {
        HandlePlayingInput();
        playerShip->Update(GetFrameTime());
        for (int i = 0; i < GameInstances.size(); i++) {
            GameInstances[i]->Update(GetFrameTime());
        }
    } 
   
    else if (currentState == GAME_OVER) {
        //HandleGameOverInput();
    }
}

void Game::Draw() {
    if (currentState == MENU) {
        //Dessiner le menu (Je vais le faire plus tard)
    } 
    else if (currentState == PLAYING) {
        playerShip->Draw();
        for (int i = 0; i < GameInstances.size(); i++) {
            GameInstances[i]->Draw();
        }
    }
    else if (currentState == GAME_OVER) {
        //Dessiner le game over (Je vais le faire plus tard)
    }
}
