// CFood.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "./file.h"
#include "./Parser.h"
#include "./Recipe.h"
#include "./EventListener.h"
#include "./Menu.h"
#include "Util.h"
#include <vector>
#include <string>

#include <direct.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <functional>

#include <locale>
#include <codecvt>

int main()
{

    char* buffer;

    // Get the current working directory:
    if ((buffer = _getcwd(NULL, 0)) == NULL)
        perror("_getcwd error");
    else
    {
        //printf("%s \nLength: %zu\n", buffer, strlen(buffer));
        free(buffer);
    }


    //std::vector<wchar_t*> fileTable;
    //file::ListDirectoryContents(&fileTable, L"Recipes");

    //std::string test = file::LoadFile(fileTable.at(0));
    //
    ////printf("%s\n", test.c_str());

    //Parser a = Parser(file::LoadFile(fileTable.at(0)), 
    //    Util::toAnsi(fileTable.at(0)));
    //a.Parse();
    //Recipe* r = a.getReceipe();
    //r->Display();
    //r->setTitle("TEST_SAVE");
    //file::saveRecipeToFile(r);
   

    std::vector<Recipe*> recipes = file::loadAllRecipes(L"Recipes");

    Menu menu;
    menu.setRecipeList(&recipes);
    menu.displayMainMenu();
    
    auto callback = [&menu](int value) {
        menu.mainMenuCallBack(value);
    };

    EventListener::setCallback(callback);
    EventListener::MainLoop();
}
