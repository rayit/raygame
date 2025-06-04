#include "raylib.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

void GameInit(void)
{
  PlayerInit();
  EnemyInit();
}

void GameUpdate(void)
{
  EnemyUpdate();
  PlayerUpdate();
}

void GameDraw(void)
{
  BeginDrawing();
  ClearBackground(RAYWHITE);

  EnemyDraw();
  PlayerDraw();
  
  EndDrawing();
}


void GameUnload(void)
{
  PlayerUnload();
  EnemyUnload();
}

