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

typedef struct Cell
{
    int i;
    int j;
} Cell;

Cell grid[COLS][ROWS];

void CellDraw(Cell);

// -------------------------------------------------------------------------------------
// Program main entry point
// -------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    // ---------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "RayIT");
    
    // Create a grid of cells
    for (int i = 0; i < COLS; i++) 
    {
        for (int j = 0; j < ROWS; j++) 
        {
            grid[i][j] = (Cell) {.i = i, .j = j};
        }
    }

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
            for (int i=0; i < COLS; i++) 
            {
                for (int j=0; j < ROWS; j++)
                {
                    CellDraw(grid[i][j]);
                }
            }
            DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing(); 
    }
    CloseWindow();
    return 0;
}

void CellDraw(Cell cell)
{
   DrawRectangleLines(cell.i * cellWidth, cell.j * cellHeight, cellWidth, cellHeight, BLACK);
}
