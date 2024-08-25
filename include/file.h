#pragma once

#include <string>
#include <vector>
#include <stdbool.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <wchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <locale>

#include "Recipe.h"

class file
{
public:
	bool static ListDirectoryContents(std::vector<wchar_t*> *fileTable, const wchar_t *sDir);
	std::string static LoadFile(const wchar_t* fileName);
	bool static saveRecipeToFile(Recipe* recipe);
	//Recipe parseRecipeFile(std::string recipeFile);


};

