#ifndef CONSTANTS_H
#define CONSTANTS_H

// تنظیمات ابعاد بازی
const int BOARD_WIDTH = 25;
const int BOARD_HEIGHT = 15;
const int BRICK_ROWS = 4;
const int BRICK_COLS = 5;
const int INITIAL_LIVES = 3;

// کدهای رنگی ANSI (برای رفع ارور تصویر دوم)
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#endif