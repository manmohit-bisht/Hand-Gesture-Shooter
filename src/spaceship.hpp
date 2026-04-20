#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>

// global variables
int hp = 7;

class Bullet {
public:
    Vector2 position;
    Vector2 velocity;
    bool active;
    bool isPlayerBullet;
    
    Bullet(Vector2 pos, Vector2 vel, bool player) : position(pos), velocity(vel), active(true), isPlayerBullet(player) {}
    
    void update() {
        position.x += velocity.x * GetFrameTime();
        position.y += velocity.y * GetFrameTime();
        
        // Remove bullets that go off screen
        if (position.y < -10 || position.y > 730) {
            active = false;
        }
    }
};

class Enemy {
public:
    Vector2 position;
    Texture2D texture;
    bool active;
    float shootTimer;
    
    Enemy(Vector2 pos) : position(pos), active(true), shootTimer(0) {}
    
    void update() {
        position.y += 100 * GetFrameTime(); // Move down
        shootTimer += GetFrameTime();
        
        // Remove enemies that go off screen
        if (position.y > 720) {
            active = false;
        }
    }
    
    bool shouldShoot() {
        return shootTimer > 2.0f; // Shoot every 2 seconds
    }
    
    void resetShootTimer() {
        shootTimer = 0;
    }
};

class Ship {
private:
    float speed;
    int leftButton;
    int rightButton;
    int fireButton;
    const char* path = "assets/PNG/playerShip1_blue.png";
    float shootCooldown;

public:
    Vector2 position;
    Texture2D texture;
    
    Ship(float speed, int leftButton, int rightButton, int fireButton)
    {
        this->speed = speed;
        this->leftButton = leftButton;
        this->rightButton = rightButton;
        this->fireButton = fireButton;
        position = {500,600};
        shootCooldown = 0;
    }

    void loadTextures()
    {
        texture = LoadTexture(path);

        if (texture.id == 0)
        {
            TraceLog(LOG_ERROR, "FAILED TO LOAD SHIP TEXTURE");
        }
    }

    void update()
    {
        float dt = GetFrameTime();
        shootCooldown -= dt;

        if (IsKeyDown(leftButton) && position.x > 0)
            position.x -= speed * dt;

        if (IsKeyDown(rightButton) && position.x < 1080 - texture.width)
            position.x += speed * dt;
    }
    
    bool canShoot() {
        return shootCooldown <= 0 && IsKeyPressed(fireButton);
    }
    
    void shoot() {
        shootCooldown = 0.3f; // 0.3 second cooldown
    }
    
    Rectangle getBounds() {
        return {position.x, position.y, (float)texture.width, (float)texture.height};
    }
};
