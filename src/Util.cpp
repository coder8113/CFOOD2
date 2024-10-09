#include "Util.h"
#include <iostream>
#include <cassert>

#include <algorithm>
#include <cstdint>
#include <string>
#include <map>
#include <vector>

#include <Windows.h>

uint32_t Util::search_recipe_list(std::vector<Recipe*>* recipe_list,
	std::string substring)
{
	std::map<std::string, std::vector<std::string>> recipeMap;

	for (Recipe* recipe : *recipe_list) {
		std::string title = recipe->title;
		std::vector<std::string> tags = recipe->tags;
		recipeMap[title] = tags;

	}

	for (uint32_t i = 0; i < recipe_list->size(); i++)
	{
		Recipe* recipe = recipe_list->at(i);
		std::string title = toLowerCase(recipe ->title);

		if (title.find(substring) != std::string::npos) {
			return i;
		}

		for (const std::string& tag : recipe->tags) {
			std::string lowerTag = toLowerCase(tag);
			if (lowerTag.find(substring) != std::string::npos) {
				return i;
			}

		}

	}


	return -1;
}

std::vector<Recipe*>* Util::filterRecipes(std::vector<Recipe*>* recipe_list, const std::string& search_term) {
	
	std::vector<Recipe*>* filtered_list = new std::vector<Recipe*>();

	// Convert search_term to lowercase for case-insensitive comparison
	std::string lowered_search_term = toLowerCase(search_term);

	for (Recipe* recipe : *recipe_list) {
		// Convert recipe title to lowercase
		std::string title = toLowerCase(recipe->title);

		// Check if search_term is a substring in the title
		bool match_in_title = (title.find(lowered_search_term) != std::string::npos);

		// Check if search_term is a substring in the tags
		bool match_in_tags = false;
		for (const std::string& tag : recipe->tags) {
			std::string lowerTag = toLowerCase(tag);

			// Check if search_term is a substring in the tag
			if (lowerTag.find(lowered_search_term) != std::string::npos) {
				match_in_tags = true;
				//break;  // No need to check other tags if a match is found
			}
		}

		// If a match is found in either the title or the tags, add the recipe to the filtered list
		if (match_in_title || match_in_tags) {
			filtered_list->push_back(recipe);
		}
	}

	return filtered_list;
}






std::vector<Recipe*>* Util::copyRecipeList(const std::vector<Recipe*>* original_list) {
	std::vector<Recipe*>* copy = new std::vector<Recipe*>();
	for (Recipe* recipe : *original_list) {
		copy->push_back(new Recipe(*recipe));
	}
	return copy;
}

std::string Util::toLowerCase(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), std::tolower);
	return str;
}

std::string Util::toAnsi(std::wstring wstr) 
{
	int RequiredLength = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wstr.data(), wstr.length(), NULL, 0, NULL, NULL);

	if (!RequiredLength)
	{
		printf("Util::toAnsi failed with error %d!\r\n", GetLastError());
		return {};
	}

	std::string str(RequiredLength, '\0');

	RequiredLength = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wstr.data(), wstr.length(), const_cast<char*>(str.data()), str.length(), NULL, NULL);

	if (!RequiredLength)
	{
		printf("Util::toAnsi failed with error %d!\r\n", GetLastError());
		return {};
	}

	return str;
}

void Util::unittest() {
	// Test toLowerCase function
	std::string input = "HeLLo WoRLD!";
	std::string expectedOutput = "hello world!";
	assert(toLowerCase(input) == expectedOutput);
	std::cout << "toLowerCase test passed." << std::endl;

	// Test toAnsi function
	std::wstring ws = L"a";
	std::string s = "a";
	assert(toAnsi(ws) == s);
	std::cout << "toAnsi test passed." << std::endl;

	// Create test recipes
	Recipe recipe1;
	recipe1.setTitle("Vegetarian Lasagna");
	recipe1.tags = { "vegetarian", "dinner" };

	Recipe recipe2;
	recipe2.setTitle("Chicken Alfredo");
	recipe2.tags = { "chicken", "dinner" };

	Recipe recipe3;
	recipe3.setTitle("Vegan Salad");
	recipe3.tags = { "vegan", "salad" };

	std::vector<Recipe*> recipeList;
	recipeList.push_back(&recipe1);
	recipeList.push_back(&recipe2);
	recipeList.push_back(&recipe3);

	// Test search_recipe_list
	assert(search_recipe_list(&recipeList, "chicken") == 1); // Should return index of Chicken Alfredo
	assert(search_recipe_list(&recipeList, "vegetarian") == 0); // Should return index of Vegetarian Lasagna
	assert(search_recipe_list(&recipeList, "salad") == 2); // Should return index of Vegan Salad
	assert(search_recipe_list(&recipeList, "non-existent") == -1); // Should return -1

	std::cout << "search_recipe_list tests passed." << std::endl;

	// Test filterRecipes
	std::vector<Recipe*>* filteredList = filterRecipes(&recipeList, "Vegan");
	assert(filteredList->size() == 1); // Should find 2 recipes (Vegetarian Lasagna and Vegan Salad)

	
	std::cout << "filterRecipes test passed." << std::endl;

	// Test copyRecipeList
	std::vector<Recipe*>* copiedList = copyRecipeList(&recipeList);
	assert(copiedList->size() == recipeList.size()); // Should copy the same number of recipes
	assert(copiedList->at(0)->title == recipeList.at(0)->title); // Check title of the first recipe
	assert(copiedList->at(1)->title == recipeList.at(1)->title); // Check title of the second recipe
	assert(copiedList->at(2)->title == recipeList.at(2)->title); // Check title of the third recipe

	

	std::cout << "copyRecipeList test passed." << std::endl;
}


