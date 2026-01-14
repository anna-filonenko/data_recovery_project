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

	if (symb >= 'A' && symb <= 'Z' ||
		symb >= 'a' && symb <= 'z')
		return true;

	return false;
}

int wordLen(const char* text, int start) {
	int len = 0;

	while (isLetter(text[start + len])) {
		len++;
	}
	return len;
}

void copyText(const char* src, char* dest) {
	int i = 0;

	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int wordStartIdx(const char* text, int chosenWordNum) {
	if (chosenWordNum <= 0)
		return -1;

	int wordNumber = 0;
	bool isInWord = false;
	int i = 0;

	while (text[i] != '\0') {
		if (isLetter(text[i])) {
			if (!isInWord)
			{
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

void corruptText(double corruptionRate, int length, char* text, char* corrupted) {
	int corruptedSymbolsNum = (int)(length * corruptionRate);
	copyText(text, corrupted);

	for (size_t i = 0; i < corruptedSymbolsNum; i++)
	{
		int bitIndex = rand() % BIT_VARIATIONS;
		int index = rand() % length;

		if (isLetter(corrupted[index]))
			corrupted[index] ^= (1 << bitIndex);
	}
}

void printCorruptedText(const char* corrupted, const char* text) {
	int i = 0;

	while (corrupted[i] != '\0')
	{
		if (corrupted[i] != text[i])
			std::cout << RED_CODE << corrupted[i] << ANSI_RESET;
		else
			std::cout << corrupted[i];
		i++;
	}
}

bool isCorrupted(const char* corrupted, const char* text, int idx) {
	if (corrupted[idx] != text[idx])
		return true;

	return false;
}

bool guessingMessages(const char* original, char* corrupted, char* options, int symbIndex, int& mistakesCount, int& guess) {
	while (true)
	{
		std::cout << "your guess: ";
		std::cin >> guess;

		if (guess<0 || guess>BIT_VARIATIONS)
		{
			std::cout << "not an option! try again: ";
			continue;
		}
		if (guess == 0) {
			return false;
		}
		char examinedSymbol = options[guess - 1];
		if (examinedSymbol == original[symbIndex])
		{
			std::cout << "you guessed!\n\n";
			corrupted[symbIndex] = original[symbIndex];
			return true;
		}
		else
			std::cout << "wrong! try again\n";
		mistakesCount++;
	}
}

bool guessing(char* corrupted, const char* original, int symbIndex, int& mistakesCount) {
	int guess;
	char options[BIT_VARIATIONS];
	char temp = corrupted[symbIndex];

	for (size_t i = 0; i < BIT_VARIATIONS; i++)
	{
		char possibleOption;
		possibleOption = temp ^ (1 << i);

		if (possibleOption < ASCII_CONTROL_CHARS || possibleOption == ASCII_DEL_CODE)
			possibleOption = original[symbIndex];

		bool isHere = false;

		for (size_t j = 0; j < i; j++)
		{
			if (options[j] == possibleOption)
			{
				isHere = true;
				break;
			}
		}
		if (isHere)
			possibleOption = original[symbIndex];

		options[i] = possibleOption;
	}

	for (size_t i = 0; i < BIT_VARIATIONS; i++)
	{
		std::cout << i + 1 << ") " << options[i] << std::endl;
	}

	std::cout << "press 0 to cancel\n";

	return guessingMessages(original, corrupted, options, symbIndex, mistakesCount, guess);
}

void printTextWithGuessedCharacters(const char* original, const char* corrupted, const char* corruptedCopy) {
	int i = 0;

	while (corrupted[i] != '\0') {
		if (corrupted[i] == original[i] && (corruptedCopy[i] != original[i]))
			std::cout << GREEN_CODE << corrupted[i] << ANSI_RESET;
		else if (corrupted[i] != original[i])
			std::cout << RED_CODE << corrupted[i] << ANSI_RESET;
		else
			std::cout << corrupted[i];
		i++;
	}
	std::cout << std::endl;
}

bool gameIsFinished(const char* text, const char* corrupted) {
	int i = 0;
	while (corrupted[i] != '\0') {
		if (corrupted[i] != text[i])
			return false;
		i++;
	}
	return true;
}

int selectWord(char* text) {
	int userWord;

	std::cout << "enter the number of the word to examine\npress -1 to save and exit\nyour choice: ";
	std::cin >> userWord;

	if (userWord < 1)
		return userWord;

	int wordStart = wordStartIdx(text, userWord);

	if (wordStart == -1)
		std::cout << "invalid word number!\n";

	return wordStart;
}

int selectSymbol(const char* text, const char* corrupted, int wordStart) {
	int userSymb;

	std::cout << "enter the number of the symbol to examine\npress 0 to cancel, -1 to save and exit\nyour choice:  ";
	std::cin >> userSymb;

	if (userSymb < 1) return userSymb;

	int symbolToExamine = wordStart + (userSymb - 1);

	if (!isCorrupted(corrupted, text, symbolToExamine)) {
		std::cout << "not a corrupted symbol!\n";
		return 0;
	}
	return symbolToExamine;
}

void displayText(char* text, char* corruptedText, char* corruptedCopy) {
	printTextWithGuessedCharacters(text, corruptedText, corruptedCopy);
	std::cout << std::endl;
}

void mainGameLoop(char* text, char* corruptedText, char* corruptedCopy, int& mistakesCount) {
	displayText(text, corruptedText, corruptedCopy);

	while (true) {
		int wordStart = selectWord(text);
		if (wordStart == 0)
			break;
		if (wordStart == -1)
		{
			saveGame("save.txt", text, corruptedText, corruptedCopy, mistakesCount);
			return;
		}

		while (true) {
			int symbolToExamine = selectSymbol(text, corruptedText, wordStart);
			if (symbolToExamine == 0)
				break;
			if (symbolToExamine == -1)
			{
				saveGame("save.txt", text, corruptedText, corruptedCopy, mistakesCount);
				return;
			}
			std::cout << "Choose what to change the selected character to: \n";

			bool isGuessed = guessing(corruptedText, text, symbolToExamine, mistakesCount);

			std::cout << CLEAR_CONSOLE;
			displayText(text, corruptedText, corruptedCopy);

			if (gameIsFinished(text, corruptedText) && isGuessed)
			{
				std::cout << "\ncongratulations! you have recovered the text and made only " << mistakesCount << " mistakes\n";
				return;
			}
			if (isGuessed)
				break;
		}
	}
}
