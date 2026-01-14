#pragma once

void saveGame(const char* save, const char* text, const char* corruptedText, const char* corruptedCopy, int attemptsCount);
bool loadGame(const char* save, char* text, char* corruptedText, char* corruptedCopy, int& attemptsCount);
bool getTextFromFile(const char* path, char* text);