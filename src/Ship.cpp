#include "Classes.h"

void Ship::Draw()
{
    DrawTriangle(ShipTrianglePoints[0], ShipTrianglePoints[1], ShipTrianglePoints[2], WHITE);
}