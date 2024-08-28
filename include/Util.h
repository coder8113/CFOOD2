/**
 * @file Util.h
 * @brief This file contains the definition of the Util class, 
 * which is responsible for the search function.
 * 
 *
 */
#pragma once
#include <vector>
#include <string>
#include <cinttypes>
#include "Recipe.h"

class Util
{
public:
	/**
     * @brief Runs unit tests for the Menu class.
     */
	static void unittest();
	
	/*!
	* Returns the index of the first instance of the substring
	* @param recipe_list recipe list to search through
	* @return first index of occurence. (-1 if no instance)
	*/
	static uint32_t search_recipe_list(std::vector<Recipe*>* recipe_list, std::string substring);
	static std::string toLowerCase(std::string str);
	static std::string toAnsi(std::wstring wstr);
private:
};

