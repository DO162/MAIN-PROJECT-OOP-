#pragma once

#include <iostream> // cout, endl
#include <fstream> // ofstream 
#include <string> // string
#include <windows.h> // HANDLE, COORD, SetConsoleCursorPosition, SetConsoleTextAttribute
#include <conio.h> // _kbhit, _getch
#pragma comment(lib, "winmm.lib") // PlaySoundA 
using namespace std;

// ---------------------- ENUMS ----------------------
enum Color : short { // цвета для SetConsoleTextAttribute
    BLACK, DARKBLUE, DARKGREEN, TURQUOISE, DARKRED,
    PURPLE, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN,
    CYAN, RED, PINK, YELLOW, WHITE
};

enum Key : short { // коды клавиш
    LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80,
    ENTER = 13, SPACE = 32, ESCAPE = 27, BACKSPACE = 8
};