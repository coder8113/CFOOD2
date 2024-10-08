#include <iostream>
#include <cassert>
#include "EventListener.h"
#include "file.h"
#include "Menu.h"
#include "Parser.h"
#include "Recipe.h"
#include "Console.h"

int main() {
	Menu::unittest();
	Parser::unittest();
	Recipe::unittest();
	file::unittest();
	Util::unittest();
	Console::unittest();
	std::cout << "Test Done!";
	return 0;
}

