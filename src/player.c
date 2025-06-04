#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include <stdio.h>

void PlayerInit(void) {
  // Position player 
  player.playerPos = (Vector2){400, 550};
}

void PlayerUpdate(void) {
  // Move player left and right with keys
  if (IsKeyDown(KEY_LEFT)) player.playerPos.x -= 5;
  if (IsKeyDown(KEY_RIGHT)) player.playerPos.x += 5;

  // check collision
  bool collision = CheckCollisionCircleRec(player.playerPos, 20, enemy.rec); 
  // if(collision == true) {
  TraceLog(LOG_INFO, "enemy rec.y: %f | enemy.pos.y: %f | Collision: %i", enemy.rec.y, enemy.pos.y, collision);
  //}
}

void PlayerDraw(void) {
  // For now draw circle (as player)
  DrawCircleV(player.playerPos, 20, DARKBLUE);
}

void PlayerUnload(void) {
  
}

