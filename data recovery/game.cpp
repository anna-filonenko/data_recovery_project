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
* <gameplay file>
*
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "constants.h"
#include "helperFunctions.h"
#include "workWithFiles.h"


void startGame() {
	std::srand(std::time(0));

	char text[MAX_TEXT_LEN];
	char corruptedText[MAX_TEXT_LEN];
	char corruptedCopy[MAX_TEXT_LEN];
	int attemptsCount = 0;
	int choice;

	std::cout << "\tMAIN MENU\n1. start a new game\n2.load last game\n";
	std::cin >> choice;

	switch (choice){
	
	case 1:
	{
		std::cin.ignore();
		char path[MAX_PATH_LEN];
		double corruptionRate;

		std::cout << "enter file path: ";
		std::cin.getline(path, MAX_PATH_LEN);
		if (!getTextFromFile(path, text)) {
			std::cout << "error! Can't open the file!" << std::endl;
			return;
		}
		int length = textLength(text);
		text[length] = '\0';
		std::cout << "enter corruption rate: ";
		std::cin >> corruptionRate;

		std::cin.ignore();
		corruptText(corruptionRate, length, text, corruptedText);
		copyText(corruptedText, corruptedCopy);

		mainGameLoop(text, corruptedText, corruptedCopy, attemptsCount);
		break;
	}
	case 2: loadGame("save.txt", text, corruptedText, corruptedCopy, attemptsCount);
		mainGameLoop(text, corruptedText, corruptedCopy, attemptsCount);
		break;

	default:std::cout << "input error";
		break;
	}
}
