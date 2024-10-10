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
	* Searches through the recipe list and returns the index of the first instance of the substring
	* @param recipe_list recipe list to search through
	* @param substring to search for
	* @return first index of occurence. (-1 if no instance)
	*/
	static uint32_t search_recipe_list(std::vector<Recipe*>* recipe_list, std::string substring);

	/**
	 * @brief Filters the list of recipes by removing recipes with no matches in title or tags.
	 * @param recipe_list recipe list to filter
	 * @param substring to filter by
	 * @return filtered list
	 */
	static std::vector<Recipe*>* filterRecipes(std::vector<Recipe*>* recipe_list, const std::string& search_term);

	/**
	 * @brief Makes a deep copy of the original recipe list
	 * @param original_list to be copied
	 * @return copied list
	 */
	static std::vector<Recipe*>* copyRecipeList(const std::vector<Recipe*>* original_list);

	/**
	 * @brief Converts all characters in a string to lower-case
	 * @param str input string
	 * @return input string converted to lower-case
	 */
	static std::string toLowerCase(std::string str);

	/**
	 * @brief converts characters to ansi
	 * @param wstr input string
	 * @return converted string
	 */
	static std::string toAnsi(std::wstring wstr);
private:
};

