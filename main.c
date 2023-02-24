/*****************************************************************************
 *
 * RayIT game development (starting)
 *
 * Trying all sort of stuff to learn RayLib
 *
 * Copyright (c) 2023 Raymond Marx (rmarx@rayit.com)
 *
 ****************************************************************************/

#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//---------------------------------------------------------------------------
// Some defines
//---------------------------------------------------------------------------
#define COLS 10
#define ROWS 10
#define NUMBER_MAX_COUNT 16

//---------------------------------------------------------------------------
// Types and Structures Definition
//---------------------------------------------------------------------------
typedef struct Cell
{
    int i;
    int j;
    bool containsMine;
    bool revealed;
    bool flagged;
} Cell;

typedef struct Basket
{
    Vector2 position;
} Basket;

typedef struct Number
{
    Vector2 position;
    bool visible;
    float fallSpeed;
} Number;

typedef enum GameState
{
    PLAYING,
    END
} GameState;

//---------------------------------------------------------------------------
// GLobal Variables Declaration
//---------------------------------------------------------------------------
const int screenWidth = 1000;
const int screenHeight = 800;

const int cellWidth = screenWidth / COLS;
const int cellHeight = screenHeight / ROWS;

GameState _state;
Cell grid[COLS][ROWS];
Texture2D flagSprite;
Texture2D _atlasBasket;
Texture2D _atlasNumber1;

Number _numbers[NUMBER_MAX_COUNT]; 

float _timeGameStarted;
float _timeGameEnded;

//---------------------------------------------------------------------------
// Module Functions Declaration (local)
//---------------------------------------------------------------------------
void GameInit(void);
void GameEnd(void);
void UpdateDrawFrame(void);
static void CellDraw(Cell);
static bool IndexIsValid(int, int);
static void CellReveal(int, int);
void UnsetNumberAt(int i);
void SetNumber(int i, Vector2 position, float fallSpeed);

// -------------------------------------------------------------------------------------
// Program main entry point
// -------------------------------------------------------------------------------------
int main(void)
{
    srand(time(0));

    // Initialization
    // ---------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "RayIT");

    flagSprite = LoadTexture("resources/flag.png");
    _atlasBasket = LoadTexture("resources/red-basket.png");
    
    GameInit();
    // Testing Model
    /*Model model = LoadModel("resources/spider.obj");
    Texture2D tex = LoadTexture("resources/bg.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
    
    Camera cam = {0};
    cam.position = (Vector3){150.0f, 150.0f, 150.0f};
    cam.target = (Vector3){0.0f, 0.0f, 0.0f};
    cam.up = (Vector3){0.0f,1.0f,0.0f};
    cam.fovy = 90.0f;
    cam.projection = CAMERA_PERSPECTIVE;

    Vector3 pos = {0.0f,0.0f,0.0f};
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);
    */
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
            
            // Also add some flags this way for testing
            grid[i][j].flagged = true;
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
        UpdateDrawFrame();
    }
    //UnloadTexture(tex);
    //UnloadModel(model);
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
    else if(cell.flagged)
    {
        Rectangle source = {0,0,flagSprite.width, flagSprite.height};
        Rectangle dest = {cell.i * cellWidth, cell.j * cellHeight, cellWidth, cellHeight};
        Vector2 origin = {0,0};

        DrawTexturePro(flagSprite, source, dest, origin, 0, Fade( WHITE, 0.3f));
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

void UnsetNumberAt(int i)
{
    
}

void SetNumberAt(int i, Vector2 position, float fallSpeed)
{

}


void GameInit(void)
{
    _state = PLAYING;
    _timeGameStarted = GetTime();

    // 
    for (int i = 0; i < NUMBER_MAX_COUNT; i++)
    {
        _numbers[i].visible = false;
        
    }
}

void GameEnd(void)
{
    _state = END;
    _timeGameEnded = GetTime();
}

void UpdateDrawFrame(void)
{
    if ( _state == END && IsKeyPressed(KEY_R))
    {
        GameInit();
    }

    // TODO winning..
    // if (win condition)
    // {
    //     GameEnd();
    // }

    BeginDrawing();

    if (_state == END)
    {
        // TODO: GameOver HUD
    } 
    else 
    {
        // TODO: Gametime HUD
    }
    ClearBackground(RAYWHITE);
    // BeginMode3D(cam);
    // DrawModel(model, pos, 1.0f, WHITE);
            
    // EndMode3D();
            

    DrawText("Click cells", 10, 10, 20, DARKGRAY);
    for (int i=0; i < COLS; i++) 
    {
        for (int j=0; j < ROWS; j++)
        {
            CellDraw(grid[i][j]);
        }
    }
    // DrawCircleV(ballPosition, 50, MAROON);

    EndDrawing();
}

