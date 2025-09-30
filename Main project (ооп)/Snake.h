#pragma once

#include "Header.h"

// ---------------------- ����� ������ ----------------------
class Snake : public GameObject { // ������
private: // ���� ������
	int** body;       // ������������ ������ [x,y] ���������
	char headChar; // ������ ������
	char bodyChar; // ������ ����
	int length; // ������� ����� ������
	int maxLength; // ������������ ����� ������
public:
	Snake(int startX, int startY, int maxLength = 0) { // ����������� � ����������� �� ���������
		headChar = '0';
		bodyChar = '*';
		this->maxLength = maxLength;
		length = 1;

		body = new int* [maxLength];
		for (int i = 0; i < maxLength; ++i) {
			body[i] = new int[2];
		}
		body[0][0] = startX; // ��������� ������� ������
		body[0][1] = startY; // ��������� ������� ������
		x = startX;
		y = startY;
	}

	~Snake() { // ����������
		for (int i = 0; i < maxLength; ++i) // ������������ ������
			delete[] body[i]; // �������� ������� ����������
		delete[] body; // �������� ��������� �������
	}

	int getLength() const { return length; } // ������ ������� ����� ������
	int** getBody() const { return body; }

	void growTo(int nx, int ny) { // ���������� ����� ������
		if (length < maxLength) { // �������� �� ������������ �����
			body[length][0] = nx; // ���������� ������ �������� � �����
			body[length][1] = ny; // ���������� ������ �������� � �����
			++length; // ���������� �����
			x = nx; // ���������� ��������� ������
			y = ny; // ���������� ��������� ������
		}
	}

	void moveTo(int nx, int ny) { // ����������� ������
		for (int i = 0; i < length - 1; ++i) { // ����� ���� ��������� �����
			body[i][0] = body[i + 1][0]; // ����� ���� ��������� �����
			body[i][1] = body[i + 1][1]; // ����� ���� ��������� �����
		}
		body[length - 1][0] = nx; // ���������� ������
		body[length - 1][1] = ny;
		x = nx; // ���������� ��������� ������
		y = ny;
	}

	void draw(HANDLE h) override { // ��������� ������
		for (int i = 0; i < length - 1; ++i) { // ������ ��� ��������, ����� ������
			COORD c{ body[i][0], body[i][1] }; // ���������� ��������
			SetConsoleCursorPosition(h, c);
			SetConsoleTextAttribute(h, Color::GREEN);
			cout << bodyChar;
		}
		COORD c{ body[length - 1][0], body[length - 1][1] }; // ���������� ������
		SetConsoleCursorPosition(h, c);
		SetConsoleTextAttribute(h, Color::GREEN);
		cout << headChar; // ������ ������
	}

	bool collidesWithSelf(int nx, int ny) const { // �������� �� ������������ � �����
		for (int i = 0; i < length - 1; ++i) { // ��������� ��� ��������, ����� ������
			if (body[i][0] == nx && body[i][1] == ny) // ���� ���������� ���������
				return true; // ������������ ���������
		}
		return false; // ������������ ���
	}
};