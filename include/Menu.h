#pragma once

#include <cstdint>
#include <windows.h>
#include <cstdio>
#include <vector>

#include "Recipe.h"

class Menu
{
public:
	void Display();
	void printSize();

	void setRecipes(std::vector<Recipe*>* recipeList);
	uint32_t printLine(std::string line);

private:
	uint32_t rows = 0;
	uint32_t cols = 0;
	uint32_t topRow = 0;

	HWND window;
	HANDLE output_handle;

	std::vector<Recipe*>* recipes;

	bool updateScreenSize();
	void displayRecipes();
};

