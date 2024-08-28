#include "Util.h"


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

void Util::unittest(){
	
}