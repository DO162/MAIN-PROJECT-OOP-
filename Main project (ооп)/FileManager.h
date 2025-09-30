#pragma once

#include "Header.h"

// ---------------------- ФАЙЛОВЫЙ МЕНЕДЖЕР ----------------------
template<typename T> // шаблонный класс для работы с файлами
class FileManager { // менеджер файлов
private:
	string filename; // имя файла
public:
	FileManager(const string& filename) { // конструктор с параметром имени файла
		this->filename = filename;
	}
	void save(const T& data) { // сохранение данных в файл
		ofstream fout(filename, ios::app); // открытие файла в режиме добавления
		if (!fout.is_open()) return; // проверка на успешное открытие
		//fout.imbue(locale(".1251")); // короткий способ для Windows-1251
		fout << data << '\n'; // запись данных
		fout.close(); // закрытие файла
	}
};