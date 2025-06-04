#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  Vector2 playerPos;
} Player;

static Player player;

void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);
void PlayerUnload(void);

#endif
