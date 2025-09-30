#pragma once

#include "Header.h"

// ---------------------- �������� �������� ----------------------
template<typename T> // ��������� ����� ��� ������ � �������
class FileManager { // �������� ������
private:
	string filename; // ��� �����
public:
	FileManager(const string& filename) { // ����������� � ���������� ����� �����
		this->filename = filename;
	}
	void save(const T& data) { // ���������� ������ � ����
		ofstream fout(filename, ios::app); // �������� ����� � ������ ����������
		if (!fout.is_open()) return; // �������� �� �������� ��������
		//fout.imbue(locale(".1251")); // �������� ������ ��� Windows-1251
		fout << data << '\n'; // ������ ������
		fout.close(); // �������� �����
	}
};