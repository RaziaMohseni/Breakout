#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

#include "Constants.h"
#include "Structures.h"
#include "Renderer.h"
#include "Logic.h"

using namespace std;

// متغیر جهانی برای سرعت بازی
int GAME_SPEED = 35; 



void runGame() {
    Paddle myPaddle = { (BOARD_WIDTH / 2) - 4, 8 };
    Ball myBall = { BOARD_WIDTH / 2, BOARD_HEIGHT - 2, 1, -1 };
    int score = 0, lives = INITIAL_LIVES;
    int highScore = getHighScore();

    Brick bricks[BRICK_ROWS][BRICK_COLS];

    
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            bricks[i][j] = { j * (BOARD_WIDTH / BRICK_COLS) + 2, i + 2, false };
        }
    }

    system("cls"); // پاک کردن صفحه قبل از شروع بازی
    while (lives > 0) {
        if (GetAsyncKeyState('A') & 0x8000) movePaddle(myPaddle, 'L');
        if (GetAsyncKeyState('D') & 0x8000) movePaddle(myPaddle, 'R');
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;

        updateBall(myBall);
        checkCollisions(myBall, myPaddle, bricks, score);
        if (score > highScore) highScore = score;

        if (checkWin(bricks)) {
            renderGame(myPaddle, myBall, bricks);
            cout << YELLOW << "\n\n\t!!! YOU WIN !!!" << RESET << endl;
            Sleep(2000);
            break;
        }

        if (myBall.y >= BOARD_HEIGHT) {
            lives--;
            myBall = { BOARD_WIDTH / 2, BOARD_HEIGHT - 2, 1, -1 };
            Beep(200, 300);
            if (lives > 0) Sleep(800);
        }

        renderGame(myPaddle, myBall, bricks);
        setCursorPosition(0, BOARD_HEIGHT + 2);
        cout << " Score: " << score << " | High Score: " << highScore << " | Lives: " << lives << "          " << endl;
        Sleep(GAME_SPEED);
    }
    saveHighScore(score);
}

void showSettings() {
    int choice = 1;
    while (true) {
        system("cls");
        cout << YELLOW << "\n\n\t=== SETTINGS ===\n" << RESET;
        cout << (choice == 1 ? GREEN " > " : "   ") << "Difficulty: " << (GAME_SPEED == 50 ? "Easy" : (GAME_SPEED == 35 ? "Normal" : "Hard")) << RESET << endl;
        cout << (choice == 2 ? GREEN " > " : "   ") << "Back to Menu" << RESET << endl;
        
        char key = _getch();
        if (key == 'w' || key == 'W') choice = 1;
        else if (key == 's' || key == 'S') choice = 2;
        else if (key == 13) {
            if (choice == 1) {
                if (GAME_SPEED == 50) GAME_SPEED = 35;
                else if (GAME_SPEED == 35) GAME_SPEED = 20;
                else GAME_SPEED = 50;
            } else break;
        }
    }
}

int main() {
    // تنظیمات کنسول و مخفی کردن کرسر
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    // نمایش خوش‌آمدگویی
    showWelcomeScreen();

    int selected = 1;
    bool exitApp = false;

    system("cls"); // فقط یک‌بار قبل از شروع حلقه اصلی منو صفحه را پاک کن

    while (!exitApp) {
        // به جای پاک کردن کل صفحه، کرسر را به (0,0) می‌بریم تا لرزش قطع شود
        setCursorPosition(0, 0);
        showMenu(selected);
        
        // استفاده از _kbhit باعث می‌شود برنامه فقط هنگام زدن دکمه واکنش نشان دهد و لرزش کمتر شود
        if (_kbhit()) {
            char key = _getch();
            if (key == 'w' || key == 'W') { if (selected > 1) selected--; }
            else if (key == 's' || key == 'S') { if (selected < 6) selected++; }
            else if (key == 13) {
                switch (selected) {
                    case 1: 
                        runGame(); 
                        system("cls"); // تمیز کردن صفحه برای بازگشت به منو
                        break;
                    
                    case 2: { // Load Game
                        system("cls");
                        cout << YELLOW << "\n\n\t=== LOAD GAME ===\n" << RESET;
                        int lastHS = getHighScore();
                        cout << "\tLast High Score: " << GREEN << lastHS << RESET << endl;
                        cout << "\n\tPress any key to return...";
                        _getch();
                        system("cls");
                        break;
                    }

                    case 3: { // Help
                        system("cls");
                        cout << YELLOW << "\n\t=== HELP ===\n" << RESET;
                        cout << "\t[A / D] : Move Left/Right\n\t[ESC]   : Exit to Menu\n";
                        cout << "\n\tPress any key...";
                        _getch(); 
                        system("cls");
                        break;
                    }

                    case 4: { // History
                        system("cls");
                        cout << YELLOW << "\n\t=== HISTORY ===\n" << RESET;
                        cout << "\tBest Record: " << GREEN << getHighScore() << RESET << endl;
                        cout << "\n\tPress any key...";
                        _getch(); 
                        system("cls");
                        break;
                    }

                    case 5: 
                        showSettings(); 
                        system("cls");
                        break;

                    case 6: 
                        exitApp = true; 
                        break;
                }
            }
        }
        Sleep(30); // وقفه کوتاه برای جلوگیری از پردازش بیش از حد و لرزش
    }

    // بازگرداندن تنظیمات کرسر قبل از خروج
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(out, &cursorInfo);
    
    return 0;
}