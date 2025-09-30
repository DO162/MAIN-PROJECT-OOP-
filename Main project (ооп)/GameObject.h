#pragma once

#include "Header.h"

// ---------------------- БАЗОВЫЙ КЛАСС ----------------------
class GameObject { // абстрактный класс для всех объектов игры
protected: // координаты объекта
	int x;
	int y;
public:
	GameObject(int x = 0, int y = 0) { // конструктор с параметрами по умолчанию
		this->x = x;
		this->y = y;
	}
	virtual void draw(HANDLE h) = 0; // чисто виртуальная функция отрисовки
	virtual ~GameObject() {} // виртуальный деструктор
	int getX() const { return x; } // геттеры и сеттеры для координат
	int getY() const { return y; } // геттеры и сеттеры для координат
	void setPosition(int nx, int ny) { x = nx; y = ny; } // сеттеры для координат
};