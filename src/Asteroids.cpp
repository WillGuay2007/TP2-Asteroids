#include "Classes.h"

ObjectType Asteroid::GetObjectType()
{
    return objType;
}

void Asteroid::Draw()
{
    DrawCircle(Position.x, Position.y, AsteroidSize * AsteroidRadius, DARKGRAY);
}

void Asteroid::Update(float dt)
{
    // Move the asteroid
    Position.x += Direction.x * Speed * dt;
    Position.y += Direction.y * Speed * dt;

    if (Position.x - (AsteroidSize * AsteroidRadius) > WIDTH) {
        Position.x = 0 - (AsteroidSize * AsteroidRadius) + 1;
    }
    else if (Position.x + (AsteroidSize * AsteroidRadius) < 0) {
        Position.x = WIDTH + (AsteroidSize * AsteroidRadius) - 1;
    }

    if (Position.y - (AsteroidSize * AsteroidRadius) > HEIGHT) {
        Position.y = 0 - (AsteroidSize * AsteroidRadius) + 1;
    }
    else if (Position.y + (AsteroidSize * AsteroidRadius) < 0) {
        Position.y = HEIGHT + (AsteroidSize * AsteroidRadius) - 1;
    }
}

int Asteroid::GetAsteroidSize() {
    return AsteroidSize;
}

float Asteroid::GetSpeed() {
    return Speed;
}

float Asteroid::GetAsteroidRadius() {
    return AsteroidRadius;
}

void Asteroid::SplitAsteroid() {
    extern Game* game;
    PlaySound(ExplodeSound);
    if (AsteroidSize - 1 == 0) {game->RemoveGameObject(this); return;};
    int NumberOfChilds = GetRandomValue(2, 3);
    for (int i = 0; i < NumberOfChilds; i++) {
        int RandomDirection = GetRandomValue(0, 360);
        int RandomDistance = GetRandomValue(10, 20);

        Vector2 SpawnOffset = {
            (cosf(RandomDirection * DEG2RAD) * RandomDistance),
            (sinf(RandomDirection * DEG2RAD) * RandomDistance)
        };

        Vector2 NewPosition = {
            Position.x + SpawnOffset.x,
            Position.y + SpawnOffset.y
        };

        Asteroid* NewAsteroid = new Asteroid(
            NewPosition,
            AsteroidSize - 1,
            Speed * 1.2f
        );
        
        game->AddGameObject(NewAsteroid);
    }
        game->RemoveGameObject(this);
}