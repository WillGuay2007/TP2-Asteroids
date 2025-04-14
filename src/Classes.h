#pragma once

#include <raylib.h>
#include <vector>

#define WIDTH 500
#define HEIGHT 500

enum ObjectType {
    SHIP,
    ASTEROID,
    PROJECTILE,
    SOUCOUPE
};

class GameObject {
    protected:
        Vector2 Position;
        Vector2 Size;
        float Rotation;
        bool isActive;
    
    public:
        GameObject(Vector2 _Position = {0, 0}, Vector2 _Size = {1, 1}, float _Rotation = 0, bool _isActive = true) 
            : Position(_Position), Size(_Size), Rotation(_Rotation), isActive(_isActive) {}
        
        virtual ~GameObject() = default;
        Vector2 GetPosition();
        Vector2 GetSize();
        void Translate(Vector2 Direction);
        void Rotate(float Rotation);
        void AddSize(Vector2 Size);
        void SetPosition(Vector2 Position);
        void SetRotation(float Rotation);
        void SetSize(Vector2 Size);
        
        virtual ObjectType GetObjectType() = 0;
        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
};

class Ship : public GameObject {
    private:
        Sound ShootSound = LoadSound("Laser_Shoot.mp3");
        ObjectType objType = SHIP;
        Vector2 ShipTrianglePoints[3];
        Vector2 Velocity;
        float Speed;
        float MaxSpeed;
        float Acceleration;
        bool Thrusting;
        float radius = 15;
        bool IsImmune = false;
        float ImmunityTimer;
        
    public:
        Ship(Vector2 startPosition, float _Speed, float _MaxSpeed, float _Acceleration, bool _Thrusting = false) : GameObject(startPosition, {30, 30}), Speed(_Speed), MaxSpeed(_MaxSpeed), Acceleration(_Acceleration), Thrusting(_Thrusting) {SetSoundVolume(ShootSound, 0.1f);};
        ~Ship() {}

        ObjectType GetObjectType() override;
        void Draw() override;
        void Update(float dt) override;
        
        void ApplyThrust(bool thrust);
        void RotateShip(float angle);
        void Shoot();
        void Hyperspace();
        Vector2 GetPoint(int Index);
        Vector2 LerpVelocityChange(Vector2 DesiredVelocityDirection, float t); // Ca va servir a ce que quand tu thrust dans une nouvelle direction, ca change pas instantanément
        Vector2 GetDirectionUnit();
        void MakeImmune(float _ImmuneTimer);
        bool ShipIsImmune();
        void VerifyImmuneTimer();
};

class Projectile : public GameObject {
    private:
        ObjectType objType = PROJECTILE;
        Vector2 Velocity;
        float LifeTime = 0;
        float MaxLifeTime;
        float Radius = 2;
        float Speed;
        
    public:
        Projectile(Vector2 position, Vector2 velocity, float maxLifeTime = 2.0f, float _Speed = 50) : GameObject(position), Velocity(velocity), MaxLifeTime(maxLifeTime), Speed(_Speed) {};
        ~Projectile(){};

        ObjectType GetObjectType() override;
        void Draw() override;
        void Update(float dt) override;
        
        bool isExpired() const;
        float GetRadius();
};

class Asteroid : public GameObject {
    private:
        Sound ExplodeSound = LoadSound("Asteroid_Explode.mp3");
        ObjectType objType = ASTEROID;
        float Speed;
        Vector2 Direction;
        float AsteroidRadius = 10;
        int AsteroidSize;  // 3 est grand, 2 est moyen, 1 est petit
        
    public:
        Asteroid(Vector2 position, int size, float _Speed) :GameObject(position), AsteroidSize(size), Speed(_Speed){
            int DirectionAngle = GetRandomValue(0, 360);
            Direction.x = cosf((DirectionAngle) * DEG2RAD);
            Direction.y = sinf((DirectionAngle) * DEG2RAD);
            SetSoundVolume(ExplodeSound, 0.1f);
        };
        ~Asteroid() {};
        
        ObjectType GetObjectType() override;
        void Draw() override;
        void Update(float dt) override;
        void SplitAsteroid();
        
        int GetAsteroidSize();
        float GetAsteroidRadius();
        float GetSpeed();
};

class Soucoupe : public GameObject {
    private:
        ObjectType objType = SOUCOUPE;
        Vector2 Velocity;
        bool isSmall;
        float ShootTimer;
        float DirectionTimer;
        Texture2D SoucoupeTexture;
        
    public:
        Soucoupe(Vector2 position, bool small = true) :GameObject(position), isSmall(small) {
            if (isSmall) {
                SoucoupeTexture = LoadTexture("small_ufo.png");
                SetSize({40, 30});
            }
            else {
                SoucoupeTexture = LoadTexture("large_ufo.png");
                SetSize({70, 50});
            }
        
            ShootTimer = 0;
            DirectionTimer = 0;
        
            float angle = GetRandomValue(0, 360) * DEG2RAD;
            float speed = isSmall ? 150.0f : 100.0f;// Les petites sont plus rapides

            Velocity.x = cosf(angle) * speed;
            Velocity.y = sinf(angle) * speed;
        };
        ~Soucoupe() {UnloadTexture(SoucoupeTexture);};
        
        ObjectType GetObjectType() override;
        void Draw() override;
        void Update(float dt) override;
        
        void Shoot(Vector2 targetPosition);
        bool IsSmall() const { return isSmall; }
};

class Game {
    private:
        enum GameState { MENU, PLAYING, GAME_OVER };
        
        GameState currentState;
        int score;
        int lives;
        int level;
        int GainLifeCheckpoint = 10000;

        Texture2D BackgroundTexture = LoadTextureFromImage(LoadImage("Background.png"));
        
        Ship* playerShip;
        std::vector<GameObject*> GameInstances;
        
    public:
        Game(int _lives, int _level) : playerShip(nullptr), score(0), lives(_lives), level(_level), currentState(MENU) {};
        ~Game() {
            if (playerShip != nullptr) {
                delete playerShip;
                playerShip = nullptr;
            }
        };
        
        void CheckGainLife();
        void Initialize();
        void StartNewLevel();
        bool CheckIfLevelIsFinished();
        void Update();
        void Draw();
        
        void GameOver();
        void CheckCollisions();
        void SpawnAsteroids(int count);
        void SpawnSoucoupe(int count);

        void DrawScore();
        void DrawLives();
        void DrawMenu();

        void LoseLife();

        void AddGameObject(GameObject* obj);
        void RemoveGameObject(GameObject* obj);
        
        void HandleMenuInput();
        void HandlePlayingInput();
        void HandleGameOverInput();

        void HandleShipCollisions();
        void HandleProjectileCollisions();
        void HandleSoucoupeCollisions();
    };