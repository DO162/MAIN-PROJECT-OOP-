#pragma once

#include "Header.h"

// ---------------------- MUSIC MANAGER ----------------------
class MusicManager { // менеджер музыки
private: // пути к файлам
	string bgPath; // путь к фону
	string overPath; // путь к окончанию игры
public:
	MusicManager(const string& bgPath = "bg.wav", const string& overPath = "gameover.wav") { // конструктор с параметрами по умолчанию
		this->bgPath = bgPath; // путь к фону
		this->overPath = overPath; // путь к окончанию игры
	}
	void start() { PlaySoundA(bgPath.c_str(), NULL, SND_ASYNC | SND_LOOP); } // запуск фоновой музыки
	void stop() { PlaySound(NULL, 0, 0); } // остановка музыки
	void playGameOver() { PlaySoundA(overPath.c_str(), NULL, SND_ASYNC); } // проигрывание музыки окончания игры
};