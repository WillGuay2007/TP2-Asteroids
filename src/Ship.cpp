#include "Classes.h"

void Ship::Draw()
{
    DrawTriangle(ShipTrianglePoints[0], ShipTrianglePoints[1], ShipTrianglePoints[2], WHITE);
}

void Ship::Update(float dt) {

}

bool Ship::isColliding(const GameObject& other) {
    return false;
}