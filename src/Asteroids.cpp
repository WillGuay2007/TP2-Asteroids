#include "Classes.h"

void Asteroid::Draw()
{
    DrawCircle(Position.x, Position.y, GetAsteroidSize() * 50, WHITE);
}

void Asteroid::Update(float dt)
{
    Position.x += Direction.x * Speed * dt;
    Position.y += Direction.y * Speed * dt;

    if (Position.x + (AsteroidSize * 50) > WIDTH) Position.x = (AsteroidSize * 50);
    if (Position.x - (AsteroidSize * 50) < 0) Position.x = WIDTH - (AsteroidSize * 50);
    if (Position.y + (AsteroidSize * 50) > HEIGHT) Position.y = (AsteroidSize * 50);
    if (Position.y - (AsteroidSize * 50) < 0) Position.y = HEIGHT - (AsteroidSize * 50);
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