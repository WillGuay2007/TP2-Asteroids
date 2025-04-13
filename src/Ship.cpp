#include "Classes.h"

ObjectType Ship::GetObjectType()
{
    return objType;
}

void Ship::Draw()
{
    // en haut (270 degrés) C'est 270 car un y positif pointe vers le bas au lieu de vers le haut
    ShipTrianglePoints[0].x = Position.x + radius * cosf((270.0f + Rotation) * DEG2RAD);
    ShipTrianglePoints[0].y = Position.y + radius * sinf((270.0f + Rotation) * DEG2RAD);
    
    // en bas a gauche (150 degrés)
    ShipTrianglePoints[1].x = Position.x + radius * cosf((150.0f + Rotation)  * DEG2RAD);
    ShipTrianglePoints[1].y = Position.y + radius * sinf((150.0f + Rotation)  * DEG2RAD);
    
    // En bas a droite (30 degrés)
    ShipTrianglePoints[2].x = Position.x + radius * cosf((30.0f + Rotation)  * DEG2RAD);
    ShipTrianglePoints[2].y = Position.y + radius * sinf((30.0f + Rotation)  * DEG2RAD);

    DrawTriangle(
        ShipTrianglePoints[0], 
        ShipTrianglePoints[1],
        ShipTrianglePoints[2], 
    WHITE);

    //Juste pour que le joueur sache ou est le devant
    DrawCircleV(ShipTrianglePoints[0], 2, RED);

}

void Ship::Update(float dt) {
    if (IsKeyDown(KEY_A)) {
        Rotate(-180 * dt);
    }
    if (IsKeyDown(KEY_D)) {
        Rotate(180 * dt);
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

bool Ship::isColliding(const GameObject& other) {
    return false;
}