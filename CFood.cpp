// CFood.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "file.h"
#include "Parser.h"

#include <vector>
#include <string>

#include <direct.h> // _getcwd
#include <stdlib.h> // free, perror
#include <stdio.h>  // printf
#include <string.h> // strlen

int main()
{

    char* buffer;

    // Get the current working directory:
    if ((buffer = _getcwd(NULL, 0)) == NULL)
        perror("_getcwd error");
    else
    {
        printf("%s \nLength: %zu\n", buffer, strlen(buffer));
        free(buffer);
    }


    std::vector<wchar_t*> fileTable;
    file::ListDirectoryContents(&fileTable, L"Recipes");

    for (wchar_t* f : fileTable) {
        wprintf(L"%s\n", f);
    }

    std::string test = file::LoadFile(fileTable.at(0));
    
    //printf("%s\n", test.c_str());

    Parser a = Parser(file::LoadFile(fileTable.at(0)));
    a.Parse();
}
