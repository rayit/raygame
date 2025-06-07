#include "raylib.h"
#include "enemy.h"
// #include "utils.h"


Enemy enemy;  // ✅ Define the actual variable here, once

void EnemyInit(void) {
  enemy.pos = (Vector2){ GetRandomValue(100, 700), 0 };
  // enemy.correctAnswer = GenerateQuestion(enemy.question);
  enemy.active = true;
  Rectangle myRect = {enemy.pos.x, enemy.pos.y, 100, 40};
  enemy.rec = myRect;
}

void EnemyUpdate(void) {
    if (enemy.active) {
        enemy.pos.y += 2;
        enemy.rec.y = enemy.pos.y;
        if (enemy.pos.y > 600) {
            enemy.active = false;  // missed
        }
    }
}

void EnemyDraw(void) {
    if (enemy.active) {
        DrawRectangleRec(enemy.rec, RED);
        // DrawRectangleV(enemy.pos, (Vector2){ 100, 40 }, RED);
        DrawText(enemy.question, enemy.pos.x + 10, enemy.pos.y + 10, 20, WHITE);
    }
}

void EnemyUnload(void) {}
