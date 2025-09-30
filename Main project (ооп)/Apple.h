#pragma once

#include "Header.h"

// ----------------------  Ћј—— яЅЋќ ј ----------------------
class Apple : public GameObject { // €блоко
public: // конструктор с параметрами по умолчанию
    Apple(int x = 0, int y = 0) { // конструктор с параметрами по умолчанию
        this->x = x;
        this->y = y;
    }
    void relocate(const GameField& field, int** snakeBody, int length) { // перемещение €блока
        int nx, ny;
        bool collision;
        do { // ищем позицию, не пересекающуюс€ с телом змейки
            nx = rand() % (field.getWidth() - 2) + 1; // случайные координаты внутри пол€
            ny = rand() % (field.getHeight() - 2) + 1; // случайные координаты внутри пол€
            collision = false; // флаг пересечени€
            for (int i = 0; i < length; ++i) { // провер€ем все сегменты змейки
                if (snakeBody[i][0] == nx && snakeBody[i][1] == ny) { // проверка на пересечение с телом змейки
                    collision = true; break; // если пересечение, ставим флаг и выходим из цикла
                }
            }
        } while (collision); // повтор€ем, пока не найдЄм подход€щую позицию    
        x = nx;
        y = ny;
    }
    void draw(HANDLE h) { // отрисовка €блока
        COORD c{ x, y }; // координаты €блока
        SetConsoleCursorPosition(h, c);
        SetConsoleTextAttribute(h, Color::RED);
        cout << 'o';
    }
};