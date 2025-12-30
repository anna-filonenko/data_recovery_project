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

const int BITS = 32;
const int MAX_PATH_LEN = 260;
const int MAX_TEXT_LEN = 500;

void takeLast6ites(unsigned char& c) {
    if (!c) {
        return;
    }
    int mask = (1 << 6) - 1;
    unsigned int masked = c & mask;
}

void decToBinary(int n, int binary[BITS]) {
    for (int i = 0; i < BITS; i++)
        binary[i] = 0;
    int i = 0;
    while (n) {
        binary[i] = n % 2;
        n /= 2;
        i++;
    }
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

//char corruptText(double corrupionRate) {
//
//}





int main() {
    std::srand(std::time(0));

    int movesCount = 0;
    char path[MAX_PATH_LEN];
    double corruptionRate;
    char text[MAX_TEXT_LEN];

    std::cout << "enter file path: ";
    std::cin.getline(path, MAX_PATH_LEN);

    std::cout << "enter corruption rate: ";
    std::cin >> corruptionRate;

}