#ifndef LOGIC_H
#define LOGIC_H

#include <fstream>
#include "Structures.h"
#include "Constants.h"

using namespace std;

void updateBall(Ball& ball) {
    ball.x += ball.vx; 
    ball.y += ball.vy;
}

void movePaddle(Paddle& paddle, char direction) {
    if (direction == 'L' && paddle.x > 0) paddle.x -= 2;
    if (direction == 'R' && paddle.x + paddle.width < BOARD_WIDTH) paddle.x += 2;
}

void checkCollisions(Ball& ball, Paddle& paddle, Brick bricks[BRICK_ROWS][BRICK_COLS], int& score) {
    if (ball.x <= 0 || ball.x >= BOARD_WIDTH - 1) ball.vx *= -1;
    if (ball.y <= 0) ball.vy *= -1;
    if (ball.y == BOARD_HEIGHT - 1 && ball.x >= paddle.x && ball.x < paddle.x + paddle.width) ball.vy *= -1;

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            if (!bricks[i][j].isDestroyed && ball.x == bricks[i][j].x && ball.y == bricks[i][j].y) {
                bricks[i][j].isDestroyed = true; ball.vy *= -1; score += 10;
            }
        }
    }
}

bool checkWin(Brick bricks[BRICK_ROWS][BRICK_COLS]) {
    for (int i = 0; i < BRICK_ROWS; i++)
        for (int j = 0; j < BRICK_COLS; j++)
            if (!bricks[i][j].isDestroyed) return false;
    return true;
}

int getHighScore() {
    int hs = 0;
    ifstream file("highscore.txt");
    if (file.is_open()) { file >> hs; file.close(); }
    return hs;
}

void saveHighScore(int score) {
    if (score > getHighScore()) {
        ofstream file("highscore.txt");
        if (file.is_open()) { file << score; file.close(); }
    }
}

#endif