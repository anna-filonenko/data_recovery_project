/**
*
* Solution to course project # 12
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Anna Filonenko
* @idnumber 2MI8000104
* @compiler VCC
*
* <functions for working with files>
*
*/

#include <iostream>
#include <fstream>
#include "constants.h"

void saveGame(const char* save, const char* text, const char* corruptedText, const char* corruptedCopy, int attemptsCount) {
	if (!save || !text || !corruptedText || !corruptedCopy)
		return;

	std::ofstream file(save);
	if (!file) {
		std::cout << "error! can't save the game";
		return;
	}
	file << text << std::endl;
	file << corruptedText << std::endl;
	file << corruptedCopy << std::endl;
	file << attemptsCount << std::endl;
	file.close();
	std::cout << "saved succesfully";
}

bool loadGame(const char* save, char* text, char* corruptedText, char* corruptedCopy, int& attemptsCount) {
	if (!save || !text || !corruptedText || !corruptedCopy)
		return false;

	std::ifstream file(save);

	if (!file) {
		std::cout << "cant't load any games.";
		return false;
	}
	file.getline(text, MAX_TEXT_LEN);
	file.getline(corruptedText, MAX_TEXT_LEN);
	file.getline(corruptedCopy, MAX_TEXT_LEN);
	file >> attemptsCount;
	file.close();
	return true;
}

bool getTextFromFile(const char* path, char* text) {
	std::ifstream file(path);
	if (!file) {
		return false;
	}
	file.getline(text, MAX_TEXT_LEN);
	file.close();
	return true;
}
