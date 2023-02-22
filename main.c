#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#define COLS 10
#define ROWS 10


const int screenWidth = 800;
const int screenHeight = 400;

const int cellWidth = screenWidth / COLS;
const int cellHeight = screenHeight / ROWS;


// -------------------------------------------------------------------------------------
// Program main entry point
// -------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    // ---------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "RayIT");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Update
        // -----------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
        
        // Draw
        // -----------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            // Draw raws
            for (int i = 0; i < COLS; i++) 
            {
                for (int j = 0; j < ROWS; j++) 
                {
                    DrawRectangleLines(i * cellWidth, j * cellHeight, cellWidth, cellHeight, BLACK);
                }
            }

            
            DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing(); 
    }
    CloseWindow();
    return 0;
}

