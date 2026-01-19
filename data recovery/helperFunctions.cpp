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
* <file with helper functions>
*
*/

#include <iostream>
#include "constants.h"
#include "workWithFiles.h"

int textLength(const char* text) {
	int i = 0;

	while (text[i] != '\0') {
		i++;
	}
	return i;
}

bool isLetter(char symb) {
	if (!symb)
		return false;

	if ((symb >= 'A' && symb <= 'Z') ||
		(symb >= 'a' && symb <= 'z'))
		return true;

	return false;
}

int wordLen(const char* text, int start) {
	if (!text || start < 0)
		return -5;
	int len = 0;

	while (isLetter(text[start + len])) {
		len++;
	}
	return len;
}

void copyText(const char* src, char* dest) {
	if (!src || !dest)
		return;

	int i = 0;

	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int wordStartIdx(const char* text, int chosenWordNum) {
	if (chosenWordNum <= 0 || !text)
		return -1;

	int wordNumber = 0;
	bool isInWord = false;
	int i = 0;

	while (text[i] != '\0') {
		if (isLetter(text[i])) {
			if (!isInWord) {
				wordNumber++;
				if (wordNumber == chosenWordNum)
					return i;
			}
			isInWord = true;
		}
		else
			isInWord = false;
		i++;
	}
	return -1;
}

bool isCorrupted(const char* corrupted, const char* text, int idx) {
	if (!corrupted || !text)
		return false;

	if (corrupted[idx] != text[idx])
		return true;

	return false;
}

void corruptText(double corruptionRate, int length, char* text, char* corrupted) {
	if (!text || !corrupted)
		return;

	bool isUsed[MAX_TEXT_LEN] = { false };
	int corruptionsCount = 0;
	int corruptedSymbolsNum = (int)(length * corruptionRate);
	copyText(text, corrupted);

	while (corruptionsCount != corruptedSymbolsNum) {
		int bitIndex = rand() % BIT_VARIATIONS;
		int index = rand() % length;
		if (isLetter(corrupted[index]) && !isUsed[index]) {
			corrupted[index] ^= (1 << bitIndex);
			isUsed[index] = true;
			corruptionsCount++;
		}
	}
}

void printCorruptedText(const char* corrupted, const char* text) {
	if (!corrupted || !text)
		return;

	int i = 0;

	while (corrupted[i] != '\0') {
		if (corrupted[i] != text[i])
			std::cout << RED_CODE << corrupted[i] << ANSI_RESET;
		else
			std::cout << corrupted[i];
		i++;
	}
}

bool wordIsCorrupted(const char* text, const char* corrupted, int wordStart) {
	if (!text || !corrupted)
		return false;

	int len = wordLen(text, wordStart);
	for (int i = 0; i < len; i++) {
		if (corrupted[wordStart + i] != text[wordStart + i])
			return true;
	}
	return false;
}

bool guessingMessages(const char* text, char* corrupted, char* options, int symbIndex, int& mistakesCount, int& guess) {
	if (!text || !corrupted || !options)
		return false;

	while (true) {
		std::cout << "your guess: ";
		std::cin >> guess;

		if (guess < 0 || guess > BIT_VARIATIONS) {
			std::cout << "not an option!";
			continue;
		}
		if (guess == 0) {
			return false;
		}
		char examinedSymbol = options[guess - 1];

		if (examinedSymbol == text[symbIndex]) {
			std::cout << "you guessed!\n\n";
			corrupted[symbIndex] = text[symbIndex];
			return true;
		}
		else
			std::cout << "wrong! try again\n";
		mistakesCount++;
	}
}

bool guessing(char* corrupted, const char* text, int symbIndex, int& mistakesCount) {
	if (!corrupted || !text)
		return false;
	int guess;
	char options[BIT_VARIATIONS];

	int correctIdx = rand() % BIT_VARIATIONS;
	options[correctIdx] = text[symbIndex];

	bool isUsed[ASCII_TOTAL] = { false };
	isUsed[text[symbIndex]] = true;

	for (size_t i = 0; i < BIT_VARIATIONS; i++)
	{
		if (i == correctIdx)
			continue;

		char option;

		do {
			option = ASCII_CONTROL_CHARS + rand() % (ASCII_TOTAL - ASCII_CONTROL_CHARS) - 1;
		} while (isUsed[option]);

		options[i] = option;
		isUsed[option] = true;
	}
	for (size_t i = 0; i < BIT_VARIATIONS; i++) {
		std::cout << i + 1 << ") " << options[i] << std::endl;
	}
	std::cout << "press 0 to cancel\n";

	return guessingMessages(text, corrupted, options, symbIndex, mistakesCount, guess);
}

void printTextWithGuessedCharacters(const char* text, const char* corrupted, const char* corruptedCopy) {
	if (!text || !corrupted)
		return;

	int i = 0;

	while (corrupted[i] != '\0') {
		if (corrupted[i] == text[i] && (corruptedCopy[i] != text[i]))
			std::cout << GREEN_CODE << corrupted[i] << ANSI_RESET;
		else if (corrupted[i] != text[i])
			std::cout << RED_CODE << corrupted[i] << ANSI_RESET;
		else
			std::cout << corrupted[i];
		i++;
	}
	std::cout << std::endl;
}

bool gameIsFinished(const char* text, const char* corrupted) {
	if (!text || !corrupted)
		return false;

	int i = 0;

	while (corrupted[i] != '\0') {
		if (corrupted[i] != text[i])
			return false;
		i++;
	}
	return true;
}

void mainGameLoop(char* text, char* corrupted, char* corruptedCopy, int& mistakesCount) {
	if (!text || !corrupted)
		return;

	int userWord, userSymb;
	printTextWithGuessedCharacters(text, corrupted, corruptedCopy);
	std::cout << std::endl;

	while (true) {
		std::cout << "Enter the number of the word to examine (-1 to save and exit)\nyour choice: ";

		std::cin >> userWord;

		if (userWord == 0)
			break;

		if (userWord == -1) {
			saveGame("save.txt", text, corrupted, corruptedCopy, mistakesCount);
			return;
		}

		int wordStart = wordStartIdx(text, userWord);

		if (wordStart == -1) {
			std::cout << "Invalid word number!\n";
			continue;
		}

		if (!wordIsCorrupted(text, corrupted, wordStart)) {
			std::cout << "This word is not corrupted!\n";
			continue;
		}

		int len = wordLen(text, wordStart);

		while (wordIsCorrupted(text, corrupted, wordStart)) {

			std::cout << "Enter the number of the symbol to examine (0 cancel, -1 save and exit)\nyour choice: ";
			std::cin >> userSymb;
			if (userSymb == 0)
				break;

			if (userSymb == -1) {
				saveGame("save.txt", text, corrupted, corruptedCopy, mistakesCount);
				return;
			}

			if (userSymb < 1 || userSymb > len) {
				std::cout << "Invalid symbol number!\n";
				continue;
			}

			int symbIndex = wordStart + (userSymb - 1);

			if (!isCorrupted(corrupted, text, symbIndex)) {
				std::cout << "Not a corrupted symbol!\n";
				continue;
			}

			if (guessing(corrupted, text, symbIndex, mistakesCount)) {
				std::cout << CLEAR_CONSOLE;
				printTextWithGuessedCharacters(text, corrupted, corruptedCopy);

				if (gameIsFinished(text, corrupted)) {
					std::cout << "\nCongratulations! You recovered the text and made " << mistakesCount << " mistake(s)\n";
					return;
				}
			}
		}
		std::cout << "\nyou have recovered a word!\n\n";
	}
}
