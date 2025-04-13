#include "Classes.h"

void Game::AddGameObject(GameObject* obj) {
    GameInstances.push_back(obj);
}

void Game::RemoveGameObject(GameObject* obj) {
    for (int i = 0; i < GameInstances.size(); i++) {
        if (GameInstances[i] == obj) {
            GameInstances.erase(GameInstances.begin() + i);
            
            delete obj;
            
            break;
        }
    }
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
    if (playerShip != nullptr) {
        playerShip->Update(GetFrameTime());
    }
}

void Game::Update() {
    if (currentState == MENU) {
        //HandleMenuInput();
    } 
    
    else if (currentState == PLAYING) {
        HandlePlayingInput();
        for (int i = 0; i < GameInstances.size(); i++) {
            GameInstances[i]->Update(GetFrameTime());
        }
        HandleShipCollisions();
    } 
   
    else if (currentState == GAME_OVER) {
        //HandleGameOverInput();
    }
}

void Game::Draw() {

    DrawTexture(
        BackgroundTexture, 
        0,
        0,
        WHITE
    );

    if (currentState == MENU) {
        //Dessiner le menu (Je vais le faire plus tard)
    } 
    else if (currentState == PLAYING) {
        for (int i = 0; i < GameInstances.size(); i++) {
            GameInstances[i]->Draw();
        }
        playerShip->Draw();
    }
    else if (currentState == GAME_OVER) {
        //Dessiner le game over (Je vais le faire plus tard)
    }
}

void Game::HandleShipCollisions() {

    if (playerShip->ShipIsImmune()) return;

    Vector2 Points[3];
    Points[0] = playerShip->GetPoint(0);
    Points[1] = playerShip->GetPoint(1);
    Points[2] = playerShip->GetPoint(2);

    for (int i = 0; i < GameInstances.size(); i++) {
        if (GameInstances[i]->GetObjectType() == ASTEROID) {
            Asteroid* currentAsteroid = dynamic_cast<Asteroid*>(GameInstances[i]);
            
            if (currentAsteroid != nullptr) {
                float asteroidRadius = currentAsteroid->GetAsteroidRadius();
                Vector2 asteroidCenter = currentAsteroid->GetPosition();

                for (int pointIndex = 0; pointIndex < 3; pointIndex++) {
                    float distance = sqrt(
                        pow(Points[pointIndex].x - asteroidCenter.x, 2) +
                        pow(Points[pointIndex].y - asteroidCenter.y, 2)
                    );

                    if (distance < asteroidRadius * currentAsteroid->GetAsteroidSize()) {
                        playerShip->MakeImmune(3);
                        currentAsteroid->SplitAsteroid();
                        break;
                    }
                }
            }
        }
    }
}



void Game::HandleProjectileCollisions() {

}
void Game::HandleAsteroidCollisions() {

}
void Game::HandleSoucoupeCollisions() {

}
