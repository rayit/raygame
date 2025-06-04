#include "raylib.h"
#include "game.h"

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
#define NUMBERS_SPEED 5.0f
#define NUMBERS_SIZE 20


int main(void)
{
  InitWindow(800, 600, "RayIT Math Defense");
  SetTargetFPS(60);


  GameInit();

  while(!WindowShouldClose())
  {
    GameUpdate();
    GameDraw();
  }

  GameUnload();
  CloseWindow();
  return 0;
}

