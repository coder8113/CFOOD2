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
	Recipe a = Recipe();
	Recipe b = Recipe();
	a.setTitle("aaaa");
	b.setTitle("bbbb");

	std::vector<Recipe*> list;
	list.push_back(&a);
	list.push_back(&b);
	
	assert(search_recipe_list(&list, "b") == 1);
	
	std::string input = "HeLLo WoRLD!";
    std::string expectedOutput = "hello world!";
    assert(toLowerCase(input) == expectedOutput);
    std::cout << "toLowerCase test passed." << std::endl;

	std::wstring ws = L"a";
	std::string s = "a";

	assert(toAnsi(ws) == s);

    
}