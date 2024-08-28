#pragma once
#include <vector>
#include <string>
#include <cinttypes>
#include "Recipe.h"

class Util
{
public:
	/*!
	* Returns the index of the first instance of the substring
	* @param recipe_list recipe list to search through
	* @return first index of occurence. (-1 if no instance)
	*/
	static uint32_t search_recipe_list(std::vector<Recipe*>* recipe_list, std::string substring);
	static std::string toLowerCase(std::string str);
private:
};

