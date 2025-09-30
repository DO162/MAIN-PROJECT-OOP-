#pragma once

#include "Header.h"

// ---------------------- ������� ����� ----------------------
class GameObject { // ����������� ����� ��� ���� �������� ����
protected: // ���������� �������
	int x;
	int y;
public:
	GameObject(int x = 0, int y = 0) { // ����������� � ����������� �� ���������
		this->x = x;
		this->y = y;
	}
	virtual void draw(HANDLE h) = 0; // ����� ����������� ������� ���������
	virtual ~GameObject() {} // ����������� ����������
	int getX() const { return x; } // ������� � ������� ��� ���������
	int getY() const { return y; } // ������� � ������� ��� ���������
	void setPosition(int nx, int ny) { x = nx; y = ny; } // ������� ��� ���������
};