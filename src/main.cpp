#include <raylib.h>

int main() 
{
    
    InitWindow(800, 600, "Window Name");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
            ClearBackground(WHITE);
            //Start drawing in this area
        EndDrawing();
    }
    
    CloseWindow();
}