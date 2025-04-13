#include "Classes.h"

void Asteroid::Draw()
{
    DrawCircle(Position.x, Position.y, AsteroidSize * AsteroidRadius, WHITE);
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

bool Asteroid::isColliding(const GameObject& other) {
    return false;
}

int Asteroid::GetAsteroidSize() {
    return AsteroidSize;
}

float Asteroid::GetSpeed() {
    return Speed;
}