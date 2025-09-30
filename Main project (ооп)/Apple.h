#pragma once

#include "Header.h"

// ---------------------- ����� ������ ----------------------
class Apple : public GameObject { // ������
public: // ����������� � ����������� �� ���������
    Apple(int x = 0, int y = 0) { // ����������� � ����������� �� ���������
        this->x = x;
        this->y = y;
    }
    void relocate(const GameField& field, int** snakeBody, int length) { // ����������� ������
        int nx, ny;
        bool collision;
        do { // ���� �������, �� �������������� � ����� ������
            nx = rand() % (field.getWidth() - 2) + 1; // ��������� ���������� ������ ����
            ny = rand() % (field.getHeight() - 2) + 1; // ��������� ���������� ������ ����
            collision = false; // ���� �����������
            for (int i = 0; i < length; ++i) { // ��������� ��� �������� ������
                if (snakeBody[i][0] == nx && snakeBody[i][1] == ny) { // �������� �� ����������� � ����� ������
                    collision = true; break; // ���� �����������, ������ ���� � ������� �� �����
                }
            }
        } while (collision); // ���������, ���� �� ����� ���������� �������    
        x = nx;
        y = ny;
    }
    void draw(HANDLE h) { // ��������� ������
        COORD c{ x, y }; // ���������� ������
        SetConsoleCursorPosition(h, c);
        SetConsoleTextAttribute(h, Color::RED);
        cout << 'o';
    }
};