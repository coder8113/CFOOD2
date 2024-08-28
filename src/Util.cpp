#include "Util.h"
#include <cassert>
#include <iostream>


uint32_t Util::search_recipe_list(std::vector<Recipe*>* recipe_list,
	std::string substring)
{

	for (uint32_t i = 0; i < recipe_list->size(); i++)
	{
		std::string title = toLowerCase(recipe_list->at(i)->title);

		if (title.find(substring) != std::string::npos) {
			return i;
		}
	}

	return -1;
}

std::string Util::toLowerCase(std::string str)
{
	std::string lowercase;


	for (uint32_t i = 0; i < str.length(); i++)
	{
		char c = str.at(i);
		if ('A' <= c && c <= 'Z')
		{
			lowercase.push_back(c + 'a' - 'A');
		}
		else
		{
			lowercase.push_back(c);
		}
	}
	return lowercase;
}

void Util::unittest() {
    // Test toLowerCase function
    std::string input = "HeLLo WoRLD!";
    std::string expectedOutput = "hello world!";
    assert(toLowerCase(input) == expectedOutput);
    std::cout << "toLowerCase test passed." << std::endl;

    // Create sample recipes for testing search_recipe_list
    Recipe recipe1;
    recipe1.setTitle("Spaghetti Carbonara");

    Recipe recipe2;
    recipe2.setTitle("Chicken Alfredo");

    Recipe recipe3;
    recipe3.setTitle("Vegetable Stir Fry");

    std::vector<Recipe*> recipe_list = { &recipe1, &recipe2, &recipe3 };

    // Test search_recipe_list function
    uint32_t index = search_recipe_list(&recipe_list, "carbonara");
    assert(index == 0); // Should find "Spaghetti Carbonara" at index 0

    index = search_recipe_list(&recipe_list, "Alfredo");
    assert(index == 1); // Should find "Chicken Alfredo" at index 1

    index = search_recipe_list(&recipe_list, "stir fry");
    assert(index == 2); // Should find "Vegetable Stir Fry" at index 2

    index = search_recipe_list(&recipe_list, "notfound");
    assert(index == -1); // Should not find "notfound" in the list

    std::cout << "search_recipe_list test passed." << std::endl;

    std::cout << "All tests passed." << std::endl;
}