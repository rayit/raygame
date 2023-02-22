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
    bool containsMine;
    bool revealed;
} Cell;

Cell grid[COLS][ROWS];

void CellDraw(Cell);
bool IndexIsValid(int, int);
void CellReveal(int, int);

// -------------------------------------------------------------------------------------
// Program main entry point
// -------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    // ---------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "RayIT");

    // Testing Model
    Model model = LoadModel("spider.obj");
    Texture2D tex = LoadTexture("haar.jpg");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
    
    Camera cam = {0};
    cam.position = (Vector3){150.0f, 150.0f, 150.0f};
    cam.target = (Vector3){0.0f, 0.0f, 0.0f};
    cam.up = (Vector3){0.0f,1.0f,0.0f};
    cam.fovy = 90.0f;
    cam.projection = CAMERA_PERSPECTIVE;

    Vector3 pos = {0.0f,0.0f,0.0f};
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    SetTargetFPS(60);


    // Create a grid of cells
    for (int i = 0; i < COLS; i++) 
    {
        for (int j = 0; j < ROWS; j++) 
        {
            grid[i][j] = (Cell) 
            {
                .i = i, 
                .j = j,
                .containsMine = false,
                .revealed = false
            };
        }
    }

    // Set mines
    int minesToPlace = (int) (ROWS * COLS * 0.1f);
    while(minesToPlace > 0) 
    {
        int i = rand() % COLS;
        int j = rand() % ROWS;
        if (!grid[i][j].containsMine)
        {
            grid[i][j].containsMine = true;
            minesToPlace--;
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

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ) 
        {
            Vector2 mPos = GetMousePosition();
            int indexI = mPos.x / cellWidth;
            int indexJ = mPos.y / cellHeight;

            if ( IndexIsValid(indexI, indexJ)) 
            {
                // grid[indexI][indexJ].revealed = true;
                CellReveal(indexI, indexJ);
            }

        }
        
        // Draw
        // -----------------------------------------------------------------------------
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            BeginMode3D(cam);
            DrawModel(model, pos, 1.0f, WHITE);
            
            EndMode3D();
            

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
    UnloadTexture(tex);
    UnloadModel(model);
    CloseWindow();
    return 0;
}

void CellDraw(Cell cell)
{
    if (cell.revealed)
    {
        if (cell.containsMine)
        {
            DrawRectangle(cell.i * cellWidth, cell.j * cellHeight, cellWidth, cellHeight, RED);
        }
        else 
        {
             DrawRectangle(cell.i * cellWidth, cell.j * cellHeight, cellWidth, cellHeight, LIGHTGRAY);

        }
    }
    DrawRectangleLines(cell.i * cellWidth, cell.j * cellHeight, cellWidth, cellHeight, BLACK);
}

bool IndexIsValid(int i, int j)
{
    return i >= 0 && i < COLS && j >=0 && j < ROWS;
}

void CellReveal(int i, int j)
{
    grid[i][j].revealed = true;

    if ( grid[i][j].containsMine ) 
    {
        // lose!
    } 
    else 
    {
        // play sound
    }
}
