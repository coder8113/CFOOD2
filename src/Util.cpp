#include "Util.h"
#include <iostream>
#include <cassert>

#include <algorithm>
#include <cstdint>

#include <Windows.h>

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

    
}