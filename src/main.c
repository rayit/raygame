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
 *       V moving basket
 *       V falling numbers
 *      alfa2:
 *       - Add sum
 *       - Add correct answer to sum..
 *       - correct spacing of answers
 *       - moving basket with mouse
 *       - prevent out of screen
 *       - background
 *       - calculations...
 *       - correct numbers
 *       - collision
 *       - SPLIT code in files..
 *      alfa3:
 *       - sound
 * Copyright (c) 2024 Raymond Marx (rmarx@rayit.com)
 *
 ****************************************************************************/

#include "raylib.h"
// #include "raymath.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//---------------------------------------------------------------------------
// Some defines
//---------------------------------------------------------------------------
#define BASKET_SOURCE_HEIGHT 90
#define BASKET_SOURCE_WIDTH 100
#define BASKET_SPEED 6.0f
#define NUMBER_MAX_COUNT 8
#define NUMBERS_SPEED 6.0f
#define NUMBERS_SIZE 20
//---------------------------------------------------------------------------
// Types and Structures Definition
//---------------------------------------------------------------------------
typedef struct Basket
{
    Vector2 position;
    Rectangle rec;
    Rectangle rec2;
} Basket;

typedef struct Number
{
    Vector2 position;
    bool visible;
    // float fallSpeed;
    // int number;
    Rectangle rec;
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

// Test of sums (should be from??)
const char *sums[] = {"25+25", "50+50", "100+100"};
// Test of answers
int answers[3][8] = {
    {0, 100, 20, 50, 60, 25, 150, 55},
    {100, 0, 50, 99, 80, 150, 200, 900},
    {100, 250, 150, 50, 200, 80, 400, 1000}
};
// Correct answers
int correctAnswers[3] = {3, 0, 4};

Number _numbers[NUMBER_MAX_COUNT]; 
Basket _basket;

//---------------------------------------------------------------------------
// Module Functions Declaration (local)
//---------------------------------------------------------------------------
void GameInit(void);
void GameEnd(void);
void UpdateDrawFrame(void);
void DrawNumbers(void);
void DrawBasket(void);
void DrawNumbersInit(void);
void ResetNumbers(void);

// -------------------------------------------------------------------------------------
// Program main entry point
// -------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    // ---------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "RayIT");
    
    // Load textures..
    _atlasBasket = LoadTexture("assets/images/red-basket.png");
    _basket.rec = (Rectangle){0, 0, BASKET_SOURCE_WIDTH, BASKET_SOURCE_HEIGHT };

    GameInit();
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Draw
        UpdateDrawFrame();
    }
    //UnloadTexture(tex);
    //UnloadModel(model);
    
    CloseWindow();
    return 0;
}

void DrawNumbersInit(void) 
{
    for (int i = 0; i < NUMBER_MAX_COUNT; i++ )
    {
        // Random X position
        _numbers[i].position.x = GetRandomValue( 10, screenWidth-10 );
        _numbers[i].visible = true;
    }
}

void DrawNumbers(void)
{
    // On screen we want to have NUMBER_MAX_COUNT on random position
    // with random speed going down..
    
    for (int i = 0; i < NUMBER_MAX_COUNT; i++ )
    {
        // Random X position
        _numbers[i].position.y = _numbers[i].position.y + NUMBERS_SPEED;
        _numbers[i].rec = (Rectangle){_numbers[i].position.x, _numbers[i].position.y, 10, 10};
        
        if (_numbers[i].visible == true) 
        {
            // This should be random number.. 
            DrawText("100", _numbers[i].position.x, _numbers[i].position.y,  NUMBERS_SIZE, RED);
        }
        
        // Check collision with basket
        // bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);
        if (CheckCollisionRecs(_basket.rec2, _numbers[i].rec) == true )  
        {
            // TODO
            _numbers[i].visible = false;
        }
    }
    ResetNumbers();
}

void ResetNumbers(void) 
{

    for (int i = 0; i < NUMBER_MAX_COUNT; i++ )
    {
        if ( _numbers[i].position.y > screenHeight) 
        {
            _numbers[i].position.y = 0;
        }
    }
}

void DrawBasket(void)
{
    // Moving x axis
    if (IsKeyDown(KEY_RIGHT)) _basket.position.x += BASKET_SPEED;
    if (IsKeyDown(KEY_LEFT)) _basket.position.x -= BASKET_SPEED;
    _basket.rec2 = (Rectangle){_basket.position.x, _basket.position.y, BASKET_SOURCE_WIDTH, BASKET_SOURCE_HEIGHT};
    DrawTextureRec(_atlasBasket, _basket.rec, _basket.position, WHITE);
}

void GameInit(void)
{
    _state = PLAYING;
    // _timeGameStarted = GetTime();
    
    // Initial position
    _basket.position.x = screenWidth/2 - BASKET_SOURCE_WIDTH/2;
    _basket.position.y = screenHeight - BASKET_SOURCE_HEIGHT -  10;
    // Initialize numbers X position
    DrawNumbersInit();
}

void GameEnd(void)
{
    _state = END;
    //_timeGameEnded = GetTime();
}

void UpdateDrawFrame(void)
{
    if ( _state == END && IsKeyPressed(KEY_R))
    {
        GameInit();
    }

    
    // if (win condition)
    // {
    //     GameEnd();
    // }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(0,0);
    if (_state == END)
    {
        // TODO: GameOver HUD
    } 
    else 
    {
        // TODO: Gametime HUD
    }
    DrawBasket();
    DrawNumbers();
    DrawText("Calculate and catch correct number!", 10, 10, 20, DARKGRAY);
    EndDrawing();
}

