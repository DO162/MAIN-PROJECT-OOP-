#pragma once

#include "Header.h"

// ---------------------- КЛАСС ПОЛЯ ----------------------
class GameField { // игровое поле
private: // размеры поля
    int width;
    int height;
public:
    GameField(int width = 70, int height = 25) { // конструктор с параметрами по умолчанию
        this->width = width;
        this->height = height;
    }
    int getWidth() const { return width; } // геттеры для размеров
    int getHeight() const { return height; }

    void drawFrame(HANDLE h) { // отрисовка рамки
        SetConsoleTextAttribute(h, Color::RED);
        for (int Y = 0; Y < height; Y++) { // цикл по строкам
            for (int X = 0; X < width; X++) { // цикл по столбцам
                char s = ' '; // символ заполнения
                if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) // если на границе
                    s = '#'; // символ границы
                cout << s; // вывод символа
            }
            cout << '\n';
        }
    }
};
