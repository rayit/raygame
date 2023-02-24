/*****************************************************************************
 *
 * RayIT game development (starting)
 *
 * Trying all sort of stuff to learn RayLib
 * 
 * IDEA: Basket moves left to right with mouse or arrows
 *       Numbers fall down and you have to use a basket to catch them
 *       In the HUB there is a sum which the outcome you need to catch..
 * TODO:
 *      alfa1:
 *       - moving basket
 *       - falling numbers
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
#define NUMBER_MAX_COUNT 16
#define NUMBER_SOURCE_WIDTH 100
#define NUMBER_SOURCE_HEIGHT 100
#define NUMBER1_SOURCE_RECTANGLE CLITERAL(Rectangle){0,0,NUMBER_SOURCE_WIDTH, NUMBER_SOURCE_HEIGHT}

//---------------------------------------------------------------------------
// Types and Structures Definition
//---------------------------------------------------------------------------
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

GameState _state;
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
void UnsetNumberAt(int i);
void DrawNumbers(void);
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
    _atlasBasket = LoadTexture("resources/red-basket.png");
    _atlasNumber1 = LoadTexture("resources/red-basket.png");

    GameInit();
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Update
        // -----------------------------------------------------------------------------
        /* EXAMPLE
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
        */
        // Draw
        // -----------------------------------------------------------------------------
        UpdateDrawFrame();
    }
    //UnloadTexture(tex);
    //UnloadModel(model);
    CloseWindow();
    return 0;
}

void UnsetNumberAt(int i)
{
    _numbers[i].visible = false;
}

void SetNumberAt(int i, Vector2 position, float fallSpeed)
{
    if ( i < 0 || i >= NUMBER_MAX_COUNT )
    {
        return;
    }
    
    _numbers[i].position = position;
    _numbers[i].fallSpeed = fallSpeed;
    _numbers[i].visible = true;
}

void DrawNumbers(void)
{
    for (int i = 0; i < NUMBER_MAX_COUNT; i++ )
    {   
        if (!_numbers[i].visible)
        {
            // continue;
        }
        // Offset position
        Vector2 position = _numbers[i].position;
        position.x = NUMBER_SOURCE_WIDTH/2;
        position.y = NUMBER_SOURCE_HEIGHT/2;

        DrawTextureRec(_atlasNumber1, NUMBER1_SOURCE_RECTANGLE, position, WHITE);
    }
}


void GameInit(void)
{
    _state = PLAYING;
    _timeGameStarted = GetTime();

    // 
    for (int i = 0; i < NUMBER_MAX_COUNT; i++)
    {
        UnsetNumberAt(i);
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
    ClearBackground(RAYWHITE);

    if (_state == END)
    {
        // TODO: GameOver HUD
    } 
    else 
    {
        // TODO: Gametime HUD
    }

    DrawText("Calculate and catch correct number!", 10, 10, 20, DARKGRAY);
    DrawNumbers();    
    EndDrawing();
}

