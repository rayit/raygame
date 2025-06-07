#include "raylib.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

Game game;

void GameInit(void)
{
  game.gamestate = GAME_STATE_MENU;
  // Menu
  GameMenuInit();

  // Game
  BulletInit();
  PlayerInit();
  EnemyInit();
}

void GameMenuInit()
{

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

