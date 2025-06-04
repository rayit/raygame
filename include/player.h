#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  Vector2 playerPos;
} Player;

static Player player;

typedef struct {
  Vector2 pos;
  Vector2 velocity;
  bool active;
} Bullet;

void BulletInit(void);
void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);
void PlayerUnload(void);

#endif
