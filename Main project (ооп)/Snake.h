#pragma once

#include "Header.h"

// ---------------------- КЛАСС ЗМЕЙКИ ----------------------
class Snake : public GameObject { // змейка
private: // тело змейки
	int** body;       // динамический массив [x,y] сегментов
	char headChar; // символ головы
	char bodyChar; // символ тела
	int length; // текущая длина змейки
	int maxLength; // максимальная длина змейки
public:
	Snake(int startX, int startY, int maxLength = 0) { // конструктор с параметрами по умолчанию
		headChar = '0';
		bodyChar = '*';
		this->maxLength = maxLength;
		length = 1;

		body = new int* [maxLength];
		for (int i = 0; i < maxLength; ++i) {
			body[i] = new int[2];
		}
		body[0][0] = startX; // начальная позиция головы
		body[0][1] = startY; // начальная позиция головы
		x = startX;
		y = startY;
	}

	~Snake() { // деструктор
		for (int i = 0; i < maxLength; ++i) // освобождение памяти
			delete[] body[i]; // удаление каждого подмассива
		delete[] body; // удаление основного массива
	}

	int getLength() const { return length; } // геттер текущей длины змейки
	int** getBody() const { return body; }

	void growTo(int nx, int ny) { // увеличение длины змейки
		if (length < maxLength) { // проверка на максимальную длину
			body[length][0] = nx; // добавление нового сегмента в конец
			body[length][1] = ny; // добавление нового сегмента в конец
			++length; // увеличение длины
			x = nx; // обновление координат головы
			y = ny; // обновление координат головы
		}
	}

	void moveTo(int nx, int ny) { // перемещение змейки
		for (int i = 0; i < length - 1; ++i) { // сдвиг всех сегментов вперёд
			body[i][0] = body[i + 1][0]; // сдвиг всех сегментов вперёд
			body[i][1] = body[i + 1][1]; // сдвиг всех сегментов вперёд
		}
		body[length - 1][0] = nx; // обновление головы
		body[length - 1][1] = ny;
		x = nx; // обновление координат головы
		y = ny;
	}

	void draw(HANDLE h) override { // отрисовка змейки
		for (int i = 0; i < length - 1; ++i) { // рисуем все сегменты, кроме головы
			COORD c{ body[i][0], body[i][1] }; // координаты сегмента
			SetConsoleCursorPosition(h, c);
			SetConsoleTextAttribute(h, Color::GREEN);
			cout << bodyChar;
		}
		COORD c{ body[length - 1][0], body[length - 1][1] }; // координаты головы
		SetConsoleCursorPosition(h, c);
		SetConsoleTextAttribute(h, Color::GREEN);
		cout << headChar; // рисуем голову
	}

	bool collidesWithSelf(int nx, int ny) const { // проверка на столкновение с собой
		for (int i = 0; i < length - 1; ++i) { // проверяем все сегменты, кроме головы
			if (body[i][0] == nx && body[i][1] == ny) // если координаты совпадают
				return true; // столкновение произошло
		}
		return false; // столкновения нет
	}
};