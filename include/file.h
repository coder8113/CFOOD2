/**
 * @file file.h
 * @brief This file is a utility class which contains file management functions
 * It interacts with the filesystem to load, save, list, and delete files, providing 
 * essential functionality for applications dealing with recipes or other data stored in files.
 */
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

#include "Recipe.h"

class file
{
public:
	bool static ListDirectoryContents(std::vector<wchar_t*> *fileTable, const wchar_t *sDir);
	std::string static LoadFile(const wchar_t* fileName);
	bool static saveRecipeToFile(Recipe* recipe);
	bool static deleteFile(std::string filename);
	//Recipe parseRecipeFile(std::string recipeFile);


};

