#include <iostream>
#include <cassert>
#include "EventListener.h"
#include "file.h"
#include "Menu.h"
#include "Parser.h"
#include "Recipe.h"


int main() {
	Menu::unittest();
	Parser::unittest();
	std::cout << "Test Done!";
	return 0;
}

