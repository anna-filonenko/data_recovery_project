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
* <main projet solution file>
*
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

const int BIT_VARIATIONS = 6;
const int MAX_PATH_LEN = 260;
const int MAX_TEXT_LEN = 500;
const char RED_CODE[] = "\x1b[91m";
const char GREEN_CODE[] = "\x1b[92m";
const char ANSI_RESET[] = "\x1b[0m";
const int ASCII_CONTROL_CHARS = 31;
const int ASCII_DEL_CODE = 127;

void saveGame(const char* save, const char* text, const char* corruptedText, const char* corruptedCopy, int attemptsCount) {
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

int wordlen(const char* text, int start) {
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

bool getTextFromFile(const char* path, char* text) {
	std::ifstream file(path);
	if (!file) {
		return false;
	}
	file.getline(text, MAX_TEXT_LEN);
	file.close();
	return true;
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

bool guessingMessages(const char* original, char* corrupted, char* options, int symbIndex, int& attemptsCount, int& guess) {
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
			attemptsCount++;
			return true;
		}
		else
			std::cout << "wrong! try again\n";
		attemptsCount++;
	}
}

bool guessing(char* corrupted, const char* original, int symbIndex, int& attemptsCount) {
	int guess;
	char options[BIT_VARIATIONS];
	char temp = corrupted[symbIndex];
	for (size_t i = 0; i < BIT_VARIATIONS; i++)
	{
		options[i] = temp ^ (1 << i);
		if (options[i] < ASCII_CONTROL_CHARS || options[i] == ASCII_DEL_CODE)
			options[i] = original[symbIndex];
	}
	int answerPosition = rand() % BIT_VARIATIONS;
	options[answerPosition] = original[symbIndex];
	//guarantee that there is a correct answer
	for (size_t i = 0; i < BIT_VARIATIONS; i++)
	{
		std::cout << i + 1 << ") " << options[i] << std::endl;
	}
	std::cout << "press 0 to cancel\n";
	return guessingMessages(original, corrupted, options, symbIndex, attemptsCount, guess);
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

void mainGameLoop(char* text, char* corruptedText, char* corruptedCopy, int& attemptsCount) {
	int userWord, userSymb;
	printTextWithGuessedCharacters(text, corruptedText, corruptedCopy);
	std::cout << std::endl;
	while (true) {
		std::cout << "enter the number of the word to examine\npress 9 to save and exit\nyour choice: ";
		std::cin >> userWord;
		if (userWord == 0)
			break;
		if (userWord == 9)
		{
			saveGame("save.txt", text, corruptedText, corruptedCopy, attemptsCount);
			return;
		}
		int wordStart = wordStartIdx(text, userWord);
		if (wordStart == -1) {
			{
				std::cout << "invalid word number!\n";
				continue;
			}
		}
		while (true)
		{
			std::cout << "enter the number of the symbol to examine\npress 0 to cancel, 9 to save and exit\n your choice:  ";
			std::cin >> userSymb;
			if (userSymb == 0)
				break;
			if (userSymb == 9)
			{
				saveGame("save.txt", text, corruptedText, corruptedCopy, attemptsCount);
				return;
			}
			int symbol = userSymb - 1;
			int symbolToExamine = wordStart + symbol;
			while (!isCorrupted(corruptedText, text, symbolToExamine))
			{
				std::cout << "not a corrupted symbol!\ntry again: ";
				std::cin >> userSymb;
				if (userSymb == 0)
					break;
				if (userSymb == 9)
				{
					saveGame("save.txt", text, corruptedText, corruptedCopy, attemptsCount);
					return;
				}
				symbol = userSymb - 1;
				symbolToExamine = wordStart + symbol;
			}
			std::cout << "Choose what to change the selected character to: \n";
			bool isGuessed = guessing(corruptedText, text, symbolToExamine, attemptsCount);
			printTextWithGuessedCharacters(text, corruptedText, corruptedCopy);
			if (gameIsFinished(text, corruptedText)&&isGuessed)
			{
				std::cout << "\ncongratulations! you have recovered the text in just " << attemptsCount << " moves";
				return;
			}
			if (!isGuessed)
				continue;

			else
				break;
		}
	}
}

int main() {
	std::srand(std::time(0));
	char text[MAX_TEXT_LEN];
	char corruptedText[MAX_TEXT_LEN];
	char corruptedCopy[MAX_TEXT_LEN];
	int attemptsCount = 0;
	int choice;
	std::cout << "\tMAIN MENU\n1. start a new game\n2.load last game\n";
	std::cin >> choice;
	switch (choice) {
	case 1:
	{
		std::cin.ignore();
		char path[MAX_PATH_LEN];
		double corruptionRate;

		std::cout << "enter file path: ";
		std::cin.getline(path, MAX_PATH_LEN);
		if (!getTextFromFile(path, text)) {
			std::cout << "error! Can't open the file!" << std::endl;
			return -1;
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
/*D:\Desktop\testTrue.txt <- the path I'm using to test the code, putting it here
so i can copy it insted of looking for it*/
