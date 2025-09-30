#pragma once

#include "Header.h"

// ---------------------- ����� ���� ----------------------
class GameField { // ������� ����
private: // ������� ����
    int width;
    int height;
public:
    GameField(int width = 70, int height = 25) { // ����������� � ����������� �� ���������
        this->width = width;
        this->height = height;
    }
    int getWidth() const { return width; } // ������� ��� ��������
    int getHeight() const { return height; }

    void drawFrame(HANDLE h) { // ��������� �����
        SetConsoleTextAttribute(h, Color::RED);
        for (int Y = 0; Y < height; Y++) { // ���� �� �������
            for (int X = 0; X < width; X++) { // ���� �� ��������
                char s = ' '; // ������ ����������
                if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) // ���� �� �������
                    s = '#'; // ������ �������
                cout << s; // ����� �������
            }
            cout << '\n';
        }
    }
};
