#pragma once

#include "Header.h"

// ---------------------- ОСНОВНОЙ КЛАСС ИГРЫ ----------------------
class Game { // основной класс игры
private:
	GameField field; // игровое поле
	Snake snake; // змейка
	Apple apple; // яблоко
	MusicManager music; // менеджер музыки
	FileManager<int> scoresFile; // файловый менеджер для рекордов
	FileManager<string> stringFile; // файловый менеджер для строк
	HANDLE h; // дескриптор консоли
	int dx, dy; // направление движения змейки
	int sleepTime; // время сна между кадрами
	static const int MAX_LENGTH = 10; // максимальная длина змейки
public:
	Game(int w = 70, int hgt = 25) : field(w, hgt), snake(w / 2, hgt / 2, 200), apple(0, 0),
		music("C:\\Users\\sdk26\\Downloads\\city-bgm-336601.WAV", "C:\\Users\\sdk26\\Downloads\\igra-ne-proidena.WAV"), scoresFile("records.txt"), stringFile("records.txt") { // конструктор с параметрами по умолчанию

		h = GetStdHandle(STD_OUTPUT_HANDLE); // получение дескриптора консоли
		dx = 1; dy = 0; // начальное движение вправо
		sleepTime = 120; // скорость игры
		//MAX_LENGTH = 200; 
		CONSOLE_CURSOR_INFO cci{ sizeof(cci), FALSE }; // скрытие курсора
		cci.bVisible = FALSE; // скрытие курсора
		SetConsoleCursorInfo(h, &cci); // скрытие курсора
		SetConsoleOutputCP(866);
		srand(time(0)); // инициализация генератора случайных чисел
		apple.relocate(field, snake.getBody(), snake.getLength()); // начальное расположение яблока
	}

	void drawInfo() { // отрисовка информации сбоку
		COORD info{ field.getWidth() + 3, 0 }; // позиция для информации
		SetConsoleOutputCP(1251);
		SetConsoleCursorPosition(h, info);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "Максимальная длина змейки: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << MAX_LENGTH;

		info.Y = 2; // позиция для информации
		SetConsoleCursorPosition(h, info);
		SetConsoleOutputCP(1251);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "Поточная длина змейки: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << snake.getLength(); // текущая длина змейки

		info.Y = 4; // позиция для информации
		SetConsoleCursorPosition(h, info);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "Количество собранных яблок: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << snake.getLength() - 1; // количество собранных яблок
		SetConsoleOutputCP(866);
	}

	void updateInfo() { // обновление информации сбоку
		COORD info{ field.getWidth() + 3, 2 }; // позиция для информации
		SetConsoleCursorPosition(h, info);
		SetConsoleOutputCP(1251);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "Поточная длина змейки: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << snake.getLength(); // текущая длина змейки

		info.Y = 4; // позиция для информации
		SetConsoleCursorPosition(h, info);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "Количество собранных яблок: ";
		SetConsoleTextAttribute(h, Color::WHITE);
		cout << snake.getLength() - 1; // количество собранных яблок
		SetConsoleOutputCP(866);
		SetConsoleTextAttribute(h, Color::GREEN);
	}

	void run() { // основной цикл игры
		system("cls"); // очистка экрана
		field.drawFrame(h); // отрисовка рамки
		drawInfo(); // отрисовка информации сбоку
		apple.draw(h); // отрисовка яблока
		snake.draw(h); // отрисовка змейки
		music.start(); // запуск музыки

		bool running = true; // флаг работы игры
		while (running) { // основной цикл игры
			Sleep(sleepTime); // задержка между кадрами
			if (_kbhit()) { // если нажата клавиша
				int k = _getch(); if (k == 0 || k == 224) k = _getch(); // обработка спец. клавиш
				switch (k) { // смена направления движения
				case Key::DOWN: dy = 1; dx = 0; break; // вниз
				case Key::UP: dy = -1; dx = 0; break; // вверх
				case Key::LEFT: dx = -1; dy = 0; break; // влево
				case Key::RIGHT: dx = 1; dy = 0; break; // вправо
				case Key::ESCAPE: running = false; break; // выход из игры
				}
			}
			int nx = snake.getX() + dx; // новые координаты головы
			int ny = snake.getY() + dy; // новые координаты головы
			if (nx == 0 || nx == field.getWidth() - 1 || ny == 0 || ny == field.getHeight() - 1) { running = false; break; } // столкновение со стеной
			if (nx == apple.getX() && ny == apple.getY()) { // съедание яблока
				snake.growTo(nx, ny); // увеличение змейки
				updateInfo(); //    
				if (snake.getLength() >= MAX_LENGTH) { running = false; break; } // проверка на максимальную длину
				apple.relocate(field, snake.getBody(), snake.getLength()); // перемещение яблока
				apple.draw(h); // отрисовка яблока
			}
			else { // обычное движение
				if (snake.collidesWithSelf(nx, ny)) { running = false; break; } // столкновение с собой
				COORD cTail{ snake.getBody()[0][0], snake.getBody()[0][1] }; // координаты хвоста для очистки
				SetConsoleCursorPosition(h, cTail); // очистка хвоста
				cout << ' '; // очистка хвоста
				snake.moveTo(nx, ny); // перемещение змейки
				snake.draw(h); // отрисовка змейки
			}
		}
		gameOver(); // окончание игры
	}

	void gameOver() { // окончание игры
		music.stop(); // остановка музыки
		music.playGameOver(); // проигрывание музыки окончания игры
		int score = snake.getLength() - 1; // количество собранных яблок
		//scoresFile.save(score);
		stringFile.save("Apples harvested: " + to_string(score)); // запись в файл
		stringFile.save("Length of the snake: " + to_string(snake.getLength())); // запись в файл
		stringFile.save("------------------------------"); // запись в файл


		SetConsoleOutputCP(1251);
		system("cls"); // очистка экрана
		//COORD pos{ (SHORT)10, (SHORT)5 };
		COORD END; // создание объекта для хранения координат завершения игры
		END.X = 52; // установка координаты X
		END.Y = 15; // установка координаты Y
		SetConsoleCursorPosition(h, END);
		SetConsoleTextAttribute(h, Color::RED);
		cout << "ИГРА ОКОНЧЕНА!" << endl;
		SetConsoleTextAttribute(h, Color::RED);
		END.X = 42; // установка координаты X
		END.Y = 17;
		SetConsoleCursorPosition(h, END);
		cout << "Ваш счет: " << score << endl;
		END.Y = 18;
		SetConsoleCursorPosition(h, END);
		cout << "Результат записан в файл records.txt" << endl;
		END.Y = 19;
		SetConsoleCursorPosition(h, END);
		cout << "Нажмите любую клавишу...";
		_getch(); // ожидание нажатия клавиши
		SetConsoleOutputCP(866);
	}
};