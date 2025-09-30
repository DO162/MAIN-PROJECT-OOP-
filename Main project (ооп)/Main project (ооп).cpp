#include "Header.h"
#include "GameObject.h"
#include "GameField.h"
#include "Snake.h"
#include "Apple.h"
#include "FileManager.h"
#include "MusicManager.h"
#include "Game.h"

int main() { // точка входа
	Game game; // создание объекта игры
	game.run(); // запуск игры
	return 0; // выход из программы
}