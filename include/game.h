#ifndef GAME_H
#define GAME_H

//---------------------------------------------------------------------------
// Some defines
//---------------------------------------------------------------------------
#define BASKET_SOURCE_HEIGHT 90
#define BASKET_SOURCE_WIDTH 100
#define BASKET_SPEED 6.0f
#define NUMBER_MAX_COUNT 8
#define NUMBERS_SPEED 5.0f
#define NUMBERS_SIZE 20
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void GameInit(void);
void GameUpdate(void);
void GameDraw(void);
void GameUnload(void);

#endif

