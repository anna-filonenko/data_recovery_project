#pragma once

int textLength(const char* text);
bool isLetter(char symb);
int wordLen(const char* text, int start);
void copyText(const char* src, char* dest);
int wordStartIdx(const char* text, int chosenWordNum);
void corruptText(double corruptionRate, int length, char* text, char* corrupted);
void printCorruptedText(const char* corrupted, const char* text);
bool isCorrupted(const char* corrupted, const char* text, int idx);
bool guessingMessages(const char* original, char* corrupted, char* options, int symbIndex, int& mistakesCount, int& guess);
bool guessing(char* corrupted, const char* original, int symbIndex, int& mistakesCount);
void printTextWithGuessedCharacters(const char* original, const char* corrupted, const char* corruptedCopy);
bool gameIsFinished(const char* text, const char* corrupted);
int selectWord(char* text);
int selectSymbol(const char* text, const char* corrupted, int wordStart);
void displayText(char* text, char* corruptedText, char* corruptedCopy);
void mainGameLoop(char* text, char* corruptedText, char* corruptedCopy, int& mistakesCount);