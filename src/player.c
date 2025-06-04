#include "raylib.h"
#include "player.h"
#include "enemy.h"

#define MAX_BULLETS 50

Bullet bullets[MAX_BULLETS];

void BulletInit(void) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].active = false;
  }
}

void PlayerInit(void) {
  // Position player 
  player.playerPos = (Vector2){400, 550};
}

void PlayerUpdate(void) {
  // Move player left and right with keys
  if (IsKeyDown(KEY_LEFT)) player.playerPos.x -= 5;
  if (IsKeyDown(KEY_RIGHT)) player.playerPos.x += 5;

  // Shooting
  if (IsKeyDown(KEY_SPACE)) {
    TraceLog(LOG_INFO, "Shooting");
    // We should active the bullets
    for (int i = 0; i < MAX_BULLETS; i++)
    {
      if (!bullets[i].active) {
        bullets[i].active = true;
        bullets[i].pos = player.playerPos;
        bullets[i].velocity = (Vector2) {0, -5};
        break;
      }
    }
  }

  // check collision
  bool collision = CheckCollisionCircleRec(player.playerPos, 20, enemy.rec); 
  if(collision == true) {
    TraceLog(LOG_INFO, "enemy rec.y: %f | enemy.pos.y: %f | Collision: %i", enemy.rec.y, enemy.pos.y, collision);
  }
}

void PlayerDraw(void) {
  // For now draw circle (as player)
  DrawCircleV(player.playerPos, 20, DARKBLUE);
}

void PlayerUnload(void) {
  
}

