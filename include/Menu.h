#pragma once

#include <cstdint>
#include <windows.h>
#include <cstdio>
#include <vector>
#include <functional>

#include "Recipe.h"
#include "EventListener.h"

class Menu
{
public:
	static void unittest();
	void Display();
	void printSize();

	void setRecipeList(std::vector<Recipe*>* recipes)
	{
		recipesList = recipes;
	}

	void displayMainMenu();
	void mainMenuCallBack(int vk);

	void displayRecipe();
	void recipeMenuCallBack(int vk);

	void selectRecipe();

	void cursorUp();
	void cursorDown();

	uint32_t printLineLeftJustified(std::string line, uint32_t indent);

private:
	uint32_t rows = 0;
	uint32_t cols = 0;
	uint32_t topRow = 0;
	uint32_t cursor = 0;

	HWND window;
	HANDLE output_handle;

	std::vector<Recipe*>* recipesList;
	Recipe* recipeToDisplay = NULL;


	void printIndent(uint32_t indent);
	bool updateScreenSize();
};

