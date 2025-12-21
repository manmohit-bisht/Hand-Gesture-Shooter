#include "spaceship.hpp"

int main()
{
    InitWindow(1080, 720, "Window Name");
    SetWindowState(FLAG_VSYNC_HINT);

    Ship ship(500, KEY_A, KEY_D, KEY_SPACE);
    ship.loadTextures();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(ship.texture, (int)ship.position.x, (int)ship.position.y, WHITE);

        EndDrawing();

        //Actions
        ship.update();
    }

    UnloadTexture(ship.texture);
    CloseWindow();
}
