#include "Classes.h"

ObjectType Soucoupe::GetObjectType()
{
    return objType;
}

void Soucoupe::Draw() {
    Rectangle source = { 
        0,
        0,
        (float)SoucoupeTexture.width,
        (float)SoucoupeTexture.height
    };
    
    Rectangle dest = { 
        Position.x,
        Position.y,
        Size.x,
        Size.y
    };
    
    Vector2 origin = { 0, 0 };
    
    DrawTexturePro(
        SoucoupeTexture,
        source,
        dest,
        origin,
        Rotation,
        WHITE
    );
}

void Soucoupe::Update(float dt) {
    Position.x += Velocity.x * dt;
    Position.y += Velocity.y * dt;
    if (Position.x - Size.x > WIDTH) {
            Position.x = 0 - Size.x;
        } else if (Position.x < 0 - Size.x) {
            Position.x = WIDTH;
        }
        
        if (Position.y > HEIGHT + Size.y) {
            Position.y = 0 - Size.y;
        } else if (Position.y < 0 - Size.y) {
            Position.y = HEIGHT;
    }
}
