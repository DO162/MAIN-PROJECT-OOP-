#pragma once

#include "Header.h"

// ---------------------- MUSIC MANAGER ----------------------
class MusicManager { // �������� ������
private: // ���� � ������
	string bgPath; // ���� � ����
	string overPath; // ���� � ��������� ����
public:
	MusicManager(const string& bgPath = "bg.wav", const string& overPath = "gameover.wav") { // ����������� � ����������� �� ���������
		this->bgPath = bgPath; // ���� � ����
		this->overPath = overPath; // ���� � ��������� ����
	}
	void start() { PlaySoundA(bgPath.c_str(), NULL, SND_ASYNC | SND_LOOP); } // ������ ������� ������
	void stop() { PlaySound(NULL, 0, 0); } // ��������� ������
	void playGameOver() { PlaySoundA(overPath.c_str(), NULL, SND_ASYNC); } // ������������ ������ ��������� ����
};