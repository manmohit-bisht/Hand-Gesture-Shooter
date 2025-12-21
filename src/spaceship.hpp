#pragma once
#include "raylib.h"

// global variables
extern int hp;

class Ship {
private:
    
    float speed;
    int leftButton;
    int rightButton;
    int fireButton;
    const char* path = "assets/PNG/playerShip1_blue.png";

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

    if (IsKeyDown(leftButton))
        position.x -= speed * dt;

    if (IsKeyDown(rightButton))
        position.x += speed * dt;
}


    
};
