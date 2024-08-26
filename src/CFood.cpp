// CFood.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "./file.h"
#include "./Parser.h"
#include "./Recipe.h"

#include <vector>
#include <string>

#include <direct.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

#include <locale>
#include <codecvt>

namespace util
{
    std::string wide_to_narrow(const wchar_t* wideStr) {
        std::wstring wstr(wideStr);

        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }
}

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
    //    util::wide_to_narrow(fileTable.at(0)));
    //a.Parse();
    //Recipe* r = a.getReceipe();
    //r->Display();
    //r->setTitle("TEST_SAVE");
    //file::saveRecipeToFile(r);
   

    std::vector<Recipe*> recipes = file::loadAllRecipes(L"Recipes");
    recipes.at(0)->Display();

}
