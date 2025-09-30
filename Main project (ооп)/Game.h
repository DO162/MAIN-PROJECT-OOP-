#pragma once

#include "Header.h"

// ---------------------- �������� ����� ���� ----------------------
class Game { // �������� ����� ����
private:
	GameField field; // ������� ����
	Snake snake; // ������
	Apple apple; // ������
	MusicManager music; // �������� ������
	FileManager<int> scoresFile; // �������� �������� ��� ��������
	FileManager<string> stringFile; // �������� �������� ��� �����
	HANDLE h; // ���������� �������
	int dx, dy; // ����������� �������� ������
	int sleepTime; // ����� ��� ����� �������
	static const int MAX_LENGTH = 10; // ������������ ����� ������
public:
	Game(int w = 70, int hgt = 25) : field(w, hgt), snake(w / 2, hgt / 2, 200), apple(0, 0),
		music("C:\\Users\\sdk26\\Downloads\\city-bgm-336601.WAV", "C:\\Users\\sdk26\\Downloads\\igra-ne-proidena.WAV"), scoresFile("records.txt"), stringFile("records.txt") { // ����������� � ����������� �� ���������

		h = GetStdHandle(STD_OUTPUT_HANDLE); // ��������� ����������� �������
		dx = 1; dy = 0; // ��������� �������� ������
		sleepTime = 120; // �������� ����
		//MAX_LENGTH = 200; 
		CONSOLE_CURSOR_INFO cci{ sizeof(cci), FALSE }; // ������� �������
		cci.bVisible = FALSE; // ������� �������
		SetConsoleCursorInfo(h, &cci); // ������� �������
		SetConsoleOutputCP(866);
		srand(time(0)); // ������������� ���������� ��������� �����
		apple.relocate(field, snake.getBody(), snake.getLength()); // ��������� ������������ ������
	}

	void drawInfo() { // ��������� ���������� �����
		COORD info{ field.getWidth() + 3, 0 }; // ������� ��� ����������
		SetConsoleOutputCP(1251);
		SetConsoleCursorPosition(h, info);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "������������ ����� ������: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << MAX_LENGTH;

		info.Y = 2; // ������� ��� ����������
		SetConsoleCursorPosition(h, info);
		SetConsoleOutputCP(1251);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "�������� ����� ������: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << snake.getLength(); // ������� ����� ������

		info.Y = 4; // ������� ��� ����������
		SetConsoleCursorPosition(h, info);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "���������� ��������� �����: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << snake.getLength() - 1; // ���������� ��������� �����
		SetConsoleOutputCP(866);
	}

	void updateInfo() { // ���������� ���������� �����
		COORD info{ field.getWidth() + 3, 2 }; // ������� ��� ����������
		SetConsoleCursorPosition(h, info);
		SetConsoleOutputCP(1251);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "�������� ����� ������: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << snake.getLength(); // ������� ����� ������

		info.Y = 4; // ������� ��� ����������
		SetConsoleCursorPosition(h, info);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "���������� ��������� �����: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << snake.getLength() - 1; // ���������� ��������� �����
		SetConsoleOutputCP(866);
		SetConsoleTextAttribute(h, Color::GREEN);
	}

	void run() { // �������� ���� ����
		system("cls"); // ������� ������
		field.drawFrame(h); // ��������� �����
		drawInfo(); // ��������� ���������� �����
		apple.draw(h); // ��������� ������
		snake.draw(h); // ��������� ������
		music.start(); // ������ ������

		bool running = true; // ���� ������ ����
		while (running) { // �������� ���� ����
			Sleep(sleepTime); // �������� ����� �������
			if (_kbhit()) { // ���� ������ �������
				int k = _getch(); if (k == 0 || k == 224) k = _getch(); // ��������� ����. ������
				switch (k) { // ����� ����������� ��������
				case Key::DOWN: dy = 1; dx = 0; break; // ����
				case Key::UP: dy = -1; dx = 0; break; // �����
				case Key::LEFT: dx = -1; dy = 0; break; // �����
				case Key::RIGHT: dx = 1; dy = 0; break; // ������
				case Key::ESCAPE: running = false; break; // ����� �� ����
				}
			}
			int nx = snake.getX() + dx; // ����� ���������� ������
			int ny = snake.getY() + dy; // ����� ���������� ������
			if (nx == 0 || nx == field.getWidth() - 1 || ny == 0 || ny == field.getHeight() - 1) { running = false; break; } // ������������ �� ������
			if (nx == apple.getX() && ny == apple.getY()) { // �������� ������
				snake.growTo(nx, ny); // ���������� ������
				updateInfo(); //    
				if (snake.getLength() >= MAX_LENGTH) { running = false; break; } // �������� �� ������������ �����
				apple.relocate(field, snake.getBody(), snake.getLength()); // ����������� ������
				apple.draw(h); // ��������� ������
			}
			else { // ������� ��������
				if (snake.collidesWithSelf(nx, ny)) { running = false; break; } // ������������ � �����
				COORD cTail{ snake.getBody()[0][0], snake.getBody()[0][1] }; // ���������� ������ ��� �������
				SetConsoleCursorPosition(h, cTail); // ������� ������
				cout << ' '; // ������� ������
				snake.moveTo(nx, ny); // ����������� ������
				snake.draw(h); // ��������� ������
			}
		}
		gameOver(); // ��������� ����
	}

	void gameOver() { // ��������� ����
		music.stop(); // ��������� ������
		music.playGameOver(); // ������������ ������ ��������� ����
		int score = snake.getLength() - 1; // ���������� ��������� �����
		//scoresFile.save(score);
		stringFile.save("Apples harvested: " + to_string(score)); // ������ � ����
		stringFile.save("Length of the snake: " + to_string(snake.getLength())); // ������ � ����
		stringFile.save("------------------------------"); // ������ � ����


		SetConsoleOutputCP(1251);
		system("cls"); // ������� ������
		//COORD pos{ (SHORT)10, (SHORT)5 };
		COORD END; // �������� ������� ��� �������� ��������� ���������� ����
		END.X = 52; // ��������� ���������� X
		END.Y = 15; // ��������� ���������� Y
		SetConsoleCursorPosition(h, END);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "���� ��������!" << endl;
		SetConsoleTextAttribute(h, Color::RED);
		END.X = 42; // ��������� ���������� X
		END.Y = 17;
		SetConsoleCursorPosition(h, END);
		cout << "��� ����: " << score << endl;
		END.Y = 18;
		SetConsoleCursorPosition(h, END);
		cout << "��������� ������� � ���� records.txt" << endl;
		END.Y = 19;
		SetConsoleCursorPosition(h, END);
		cout << "������� ����� �������...";
		_getch(); // �������� ������� �������
		SetConsoleOutputCP(866);
	}
};