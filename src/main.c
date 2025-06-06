#include "raylib.h"
#include "game.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RayIT Math Defense");
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

