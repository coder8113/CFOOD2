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
#include <cstdio> 
#include <codecvt>

#include "Recipe.h"
#include "Parser.h"

class file
{
public:
	bool static ListDirectoryContents(std::vector<wchar_t*> *fileTable, const wchar_t *sDir);

	std::vector<Recipe*> static loadAllRecipes(const wchar_t *sDir);

	std::string static LoadFile(const wchar_t* fileName);
	bool static saveRecipeToFile(Recipe* recipe);
	bool static deleteFile(std::string filename);
	//Recipe parseRecipeFile(std::string recipeFile);
private:
	std::string static wcharToString(const wchar_t* wstr);

};

