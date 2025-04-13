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
        virtual bool isColliding(const GameObject& objectType) = 0;
};

class Ship : public GameObject {
    private:
        ObjectType objType = SHIP;
        Vector2 ShipTrianglePoints[3];
        Vector2 Velocity;
        float Speed;
        float MaxSpeed;
        float Acceleration;
        bool Thrusting;
        float radius = 15;
        
    public:
        Ship(Vector2 startPosition, float _Speed, float _MaxSpeed, float _Acceleration, bool _Thrusting = false) : GameObject(startPosition, {30, 30}), Speed(_Speed), MaxSpeed(_MaxSpeed), Acceleration(_Acceleration), Thrusting(_Thrusting) {};
        
        ObjectType GetObjectType() override;
        void Draw() override;
        void Update(float dt) override;
        bool isColliding(const GameObject& other) override;
        
        void ApplyThrust(bool thrust);
        void RotateShip(float angle);
        void Shoot();
        void Hyperspace();
};

class Projectile : public GameObject {
    private:
        ObjectType objType = PROJECTILE;
        Vector2 Velocity;
        float LifeTime;
        float MaxLifeTime;
        
    public:
        Projectile(Vector2 position, Vector2 velocity, float maxLifeTime = 2.0f) : GameObject(position), Velocity(velocity), MaxLifeTime(maxLifeTime) {};
        
        ObjectType GetObjectType() override;
        void Draw() override;
        void Update(float dt) override;
        bool isColliding(const GameObject& other) override;
        
        bool isExpired() const;
};

class Asteroid : public GameObject {
    private:
        ObjectType objType = ASTEROID;
        float Speed;
        Vector2 Direction;
        float AsteroidRadius = 25;
        int AsteroidSize;  // 3 est grand, 2 est moyen, 1 est petit
        
    public:
        Asteroid(Vector2 position, int size, float _Speed) :GameObject(position), AsteroidSize(size), Speed(_Speed){
            if (GetRandomValue(0,1) == 1) Direction.x = 1; else Direction.x = -1;
            if (GetRandomValue(0,1) == 1) Direction.y = 1; else Direction.y = -1;
        };
        
        ObjectType GetObjectType() override;
        void Draw() override;
        void Update(float dt) override;
        bool isColliding(const GameObject& other) override;
        void SplitAsteroid();
        
        int GetAsteroidSize();
        float GetSpeed();
};

class Soucoupe : public GameObject {
    private:
        ObjectType objType = SOUCOUPE;
        Vector2 Velocity;
        bool isSmall;
        float ShootTimer;
        float DirectionTimer;
        
    public:
        Soucoupe(Vector2 position, bool small);
        
        ObjectType GetObjectType() override;
        void Draw() override;
        void Update(float dt) override;
        bool isColliding(const GameObject& other) override;
        
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
        
        void Initialize();
        void Update();
        void Draw();
        
        void StartNewGame();
        void GameOver();
        void CheckCollisions();
        void SpawnAsteroids(int count);
        void SpawnSoucoupe();

        void AddGameObject(GameObject* obj);
        
        void HandleMenuInput();
        void HandlePlayingInput();
        void HandleGameOverInput();
    };