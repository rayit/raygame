#include "raylib.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

#define MAX_BULLETS 50
#define FIRE_COOLDOWN .3f // 300 ms between shots

Player player;

// player texture
Texture2D soldier; 
Bullet bullets[MAX_BULLETS];

float timeSinceLastShot = 0.0f; // 300 ms

void BulletInit(void) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].active = false;
  }
}

void PlayerInit(void) {
  // Position player 
  Image soldierImage = LoadImage("assets/images/soldier.png");
  ImageResize(&soldierImage, 96, 96);    

  soldier = LoadTextureFromImage(soldierImage); 
  player.playerTex = soldier;  
  // Position player
  player.playerPos = (Vector2){400, 550};
}

void PlayerUpdate(void) {
  // Move player left and right with keys
  if (IsKeyDown(KEY_LEFT)) player.playerPos.x -= 5;
  if (IsKeyDown(KEY_RIGHT)) player.playerPos.x += 5;

  // Shooting
  float deltaTime = GetFrameTime();
  timeSinceLastShot += deltaTime;
  
  if (IsKeyDown(KEY_SPACE) && timeSinceLastShot >= FIRE_COOLDOWN) {
    TraceLog(LOG_INFO, "Shooting");
    // We should active the bullets
    for (int i = 0; i < MAX_BULLETS; i++)
    {
      if (!bullets[i].active) {
        bullets[i].active = true;
        bullets[i].pos = (Vector2) {player.playerPos.x, player.playerPos.y - player.playerTex.height};
        bullets[i].velocity = (Vector2) {0, -5};
        timeSinceLastShot = 0.0f;
        break;
      }
    }
  }

  // Bullet Move
  for (int i=0; i< MAX_BULLETS; i++)
  {
    if(bullets[i].active)
    {
      bullets[i].pos.x += bullets[i].velocity.x;
      bullets[i].pos.y += bullets[i].velocity.y;

      // Deactive if iff-screen
      if (bullets[i].pos.y < 0) bullets[i].active = false;
    }
  }

  // check collision
  bool collision = CheckCollisionCircleRec(player.playerPos, 20, enemy.rec); 
  if(collision == true) {
    TraceLog(LOG_INFO, "enemy rec.y: %f | enemy.pos.y: %f | Collision: %i", 
        enemy.rec.y, enemy.pos.y, collision);
  }
}

void PlayerDraw(void) {

  // Draw bullets (active)
  for (int i=0; i < MAX_BULLETS; i++ )
  {
    if ( bullets[i].active ) {
      DrawCircleV(bullets[i].pos, 3, RED);
    }
  }

  // draw player
  DrawTexture(player.playerTex, player.playerPos.x - player.playerTex.width/2, SCREEN_HEIGHT - player.playerTex.height, WHITE);
}

void PlayerUnload(void) {
  UnloadTexture(soldier); 
}

