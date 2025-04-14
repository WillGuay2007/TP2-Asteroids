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
    IsImmune ? BLUE : GRAY); // Si le joueur est temporairement invincible, il sera bleu. Sinon, gris.

    //Juste pour que le joueur sache ou est le devant
    DrawCircleV(ShipTrianglePoints[0], 2, RED);

}

void Ship::Update(float dt) {

    VerifyImmuneTimer();

    // Si il sort de l'écran
    if (Position.x - radius > WIDTH) {
        Position.x = 0 - radius;
    }
    else if (Position.x + radius < 0) {
        Position.x = WIDTH + radius;
    }

    if (Position.y - radius > HEIGHT) {
        Position.y = 0 - radius;
    }
    else if (Position.y + radius < 0) {
        Position.y = HEIGHT + radius;
    }


    if (Thrusting) {
 
        Velocity = LerpVelocityChange(GetDirectionUnit(), 0.1f); // Ca ajoute de la friction au vaisseau comme ca il change pas de direction d'un coup
    
        Speed += Acceleration * dt;
        if (Speed > MaxSpeed) Speed = MaxSpeed;
    } else {
        Speed *= 0.99;
    } // Pour plus tard
    Position.x += Velocity.x * Speed * dt;
    Position.y += Velocity.y * Speed * dt;


    if (IsKeyDown(KEY_A)) {
        Rotate(-270 * dt);
    }
    if (IsKeyDown(KEY_D)) {
        Rotate(270 * dt);
    }
    if (IsKeyPressed(KEY_SPACE)) {
        if (!IsImmune) {
            Shoot();
        }
    }
    if (IsKeyDown(KEY_S)) {
        Speed -= (Acceleration * dt / 2);
        if (Speed < 0) Speed = 0;
    }
    if (IsKeyDown(KEY_W)) {
        Thrusting = true;
    } else {
        Thrusting = false;
    }
}

Vector2 Ship::LerpVelocityChange(Vector2 DesiredVelocityDirection, float t) {
    return {
        Velocity.x + (DesiredVelocityDirection.x - Velocity.x) * t,
        Velocity.y + (DesiredVelocityDirection.y - Velocity.y) * t
    };
}

Vector2 Ship::GetPoint(int Index) {
    return ShipTrianglePoints[Index];
}

void Ship::MakeImmune(float _ImmuneTimer) {
    ImmunityTimer = _ImmuneTimer;
    IsImmune = true;
}

bool Ship::ShipIsImmune() {
    return IsImmune;
}

void Ship::VerifyImmuneTimer() {
    if (IsImmune && ImmunityTimer <= 0) {
        IsImmune = false;
        ImmunityTimer = 0;
    } else if (IsImmune) {
        ImmunityTimer -= GetFrameTime();
    }
}

Vector2 Ship::GetDirectionUnit() {
    return Vector2 {
        cosf((270.0f + Rotation) * DEG2RAD),
        sinf((270.0f + Rotation) * DEG2RAD)
    };
}

void Ship::Shoot() {
    extern Game* game;
    PlaySound(ShootSound);
    Vector2 ProjectilePosition = {
        ShipTrianglePoints[0].x,
        ShipTrianglePoints[0].y
    };
    Vector2 ProjectileVelocity = {
        GetDirectionUnit().x,
        GetDirectionUnit().y
    };
    Projectile* newProjectile = new Projectile(ProjectilePosition, ProjectileVelocity, 3, 250);
    game->AddGameObject(newProjectile);
}