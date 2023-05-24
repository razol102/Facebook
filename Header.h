#ifndef __HEADER_H
#define __HEADER_H

#pragma warning (disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Facebook.h"

void menu(Facebook& f);
void menuOptions();
void setFacebookData(Facebook& f);

void loadFromFile(std::ifstream& inFile, Facebook& f);
void saveToFile(Facebook& f, std::ofstream & outFile);

void isValidChoice(const int num, const int min, const int max);

#endif // __HEADER_H