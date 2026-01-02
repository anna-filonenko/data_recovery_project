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

const int MAX_PATH_LEN = 260;
const int MAX_TEXT_LEN = 500;
const char RED_CODE[] = "\x1b[31m";
const char ANSI_RESET[] = "\x1b[0m";

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

void copyText(const char* src, char* dest) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
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
	int corruptedSymbolsNum = (length * corruptionRate);
	copyText(text, corrupted);
	for (size_t i = 0; i < corruptedSymbolsNum; i++)
	{
		int bitIndex = rand() % 6;
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
		{
			std::cout << RED_CODE << corrupted[i] << ANSI_RESET;
		}
		else
			std::cout << corrupted[i];
		i++;
	}
}






int main() {
	std::srand(std::time(0));

	int movesCount = 0;
	char path[MAX_PATH_LEN];
	double corruptionRate;
	char text[MAX_TEXT_LEN];
	char corruptedText[MAX_TEXT_LEN];

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

	corruptText(corruptionRate, length, text,corruptedText);
	printCorruptedText(corruptedText, text);

	/*D:\Desktop\testTrue.txt <- the path I'm using to test the code, putting it here
	so i can copy it insted of looking for it*/
}