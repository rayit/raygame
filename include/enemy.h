#ifndef ENEMY_H
#define ENEMY_H

typedef struct Enemy {
    Vector2 pos;
    Rectangle rec;
    char question[64];
    bool active;
    int correctAnswer;
} Enemy;

extern Enemy enemy;  // ✅ Declare, don't define

void EnemyInit(void);
void EnemyUpdate(void);
void EnemyDraw(void);
void EnemyUnload(void);

#endif

