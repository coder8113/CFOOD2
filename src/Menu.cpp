#include "./Menu.h"
#include <iostream>

void Menu::Display()
{

}

void Menu::printSize()
{
    updateScreenSize();
    printf("rows: %d\n", rows);
    printf("cols: %d\n", cols);

}


bool Menu::updateScreenSize()
{
    /* At this point, our process has a console window assigned to it */
    window = GetConsoleWindow();
    output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    /* Grab the default size as given to us by the OS */
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;

    if (!GetConsoleScreenBufferInfo(output_handle, &buffer_info)) {
        return false;
    }

    /* Don't show the console cursor */
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 1;
    cursor_info.bVisible = false;

    if (!SetConsoleCursorInfo(output_handle, &cursor_info)) {
        return false;
    }


    cols = buffer_info.srWindow.Right - buffer_info.srWindow.Left;
    rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top;

    return true;
}
// todo: there must be a better way
uint32_t Menu::printLineLeftJustified(std::string line, uint32_t indent=0)
{
    if (line.size() < cols)
    {
        printIndent(indent);
        printf("%s\n", line.c_str());
        return 1;
    }

    uint32_t rows_printed = 1;
    uint32_t base_index = 0;
    uint32_t span = 0;
    uint32_t last_white_space_offset = 0;
  
    while (true)
    {
        if (base_index + span == line.size())
        {
            printIndent(indent);
            printf("%s\n", line.substr(base_index, span).c_str());

            return rows_printed;
        }

        if (span >= cols - 1)
        {
            if (last_white_space_offset != 0)
            {
                printIndent(indent);
                printf("%s\n", line.substr(base_index, last_white_space_offset).c_str());

                base_index += last_white_space_offset;
                span = 0;
                rows_printed++;
            }
            else
            {
                printIndent(indent);
                printf("%s-\n", line.substr(base_index, span).c_str());

                base_index += span;
                span = 0;
                rows_printed++;
            }
        }
        if (isspace(line.at(base_index + span)))
        {
            last_white_space_offset = span;
        }

        span++;
    }
   

}

void Menu::printIndent(uint32_t indent=0)
{
    for (uint32_t i = 0; i < indent; i++)
    {
        printf(" ");
    }
}


void Menu::displayMainMenu()
{
    system("cls");
    updateScreenSize();

    uint32_t LINES_RESERVED = 3;
    if (substring_to_search.size() == 0)
    {
        printf("\n");
    }
    else
    {
        printf("Search: %s\n", substring_to_search.c_str());
    }
    printf("Recipes: \n");

    uint32_t i = topRow;
    while(i < topRow + cols - LINES_RESERVED && i < recipesList->size())
    {
        if (i == cursor)
        {
            printLineLeftJustified("> " + recipesList->at(i)->title, 2);
        }
        else 
        {
            printLineLeftJustified(recipesList->at(i)->title, 4);
        }
        i++;
    }
}

void Menu::cursorUp()
{
    cursor -= cursor != 0 ? 1 : 0;
}

void Menu::cursorDown()
{
    cursor += cursor != recipesList->size() - 1 ? 1 : 0;
}

void Menu::selectRecipe()
{
    recipeToDisplay = recipesList->at(cursor);
}

void Menu::addLetterToSearch(char c)
{
    substring_to_search.push_back(c);
    uint32_t index = Util::search_recipe_list(recipesList, substring_to_search);
    if (index == -1)
    {
        return;
    }
    cursor = index;

}

void Menu::resetSearch()
{
    substring_to_search.clear();
}

void Menu::mainMenuCallBack(int vk)
{
    int VK_A = 0x41;
    int VK_Z = 0x5A;
    auto recipe_callback = [this](int value) {
        this->recipeMenuCallBack(value);
    };
    switch (vk) {
    case (VK_UP):
        resetSearch();
        cursorUp();
        displayMainMenu();
        break;
    case (VK_DOWN):
        resetSearch();
        cursorDown();
        displayMainMenu();
        break;
    case (VK_RETURN):
        resetSearch();
        selectRecipe();
        EventListener::setCallback(recipe_callback);
        displayRecipe();
        break;
    case (VK_BACK):
        resetSearch();
        displayMainMenu();
        break;
    default:
        if (VK_A <= vk && vk <= VK_Z)
        {
            addLetterToSearch(vk - VK_A + 'a');
            displayMainMenu();
        }
        break;

    }

}

void Menu::recipeMenuCallBack(int vk)
{
    auto callback = [this](int value) {
        mainMenuCallBack(value);
    };

    if (vk == VK_BACK)
    {
        EventListener::setCallback(callback);
        displayMainMenu();

    }
    return;
}

void Menu::displayRecipe()
{
    system("cls");
    if (!recipeToDisplay)
    {
        return;
    }

    std::vector<std::string> recipe = recipeToDisplay->toStringArray();

    for (std::string line : recipe)
    {
        printLineLeftJustified(line, 0);
    }

}

void Menu::unittest(){
    Menu menu;

    // Setup a mock list of recipes
    std::vector<Recipe*> recipes;
    Recipe recipe1, recipe2, recipe3;
    recipe1.setTitle("Pasta");
    recipe2.setTitle("Salad");
    recipe3.setTitle("Pizza");

    recipes.push_back(&recipe1);
    recipes.push_back(&recipe2);
    recipes.push_back(&recipe3);

    // Assign the recipes to the menu
    menu.setRecipeList(&recipes);

    // Test displayMainMenu and menu navigation
    std::cout << "Testing displayMainMenu" << std::endl;
    menu.displayMainMenu();

    std::cout << "Testing cursor movement" << std::endl;
    menu.cursorDown();
    menu.displayMainMenu(); // Expect cursor to move to the next recipe

    menu.cursorUp();
    menu.displayMainMenu(); // Expect cursor to move back to the first recipe

    // Test selecting a recipe
    std::cout << "Testing recipe selection" << std::endl;
    menu.selectRecipe();
    menu.displayRecipe(); // Expect the recipe details of the selected recipe to be displayed

    // Test printSize (indirectly testing updateScreenSize)
    std::cout << "Testing screen size printing" << std::endl;
    menu.printSize(); // Should print the number of rows and columns in the console window

    // Test adding letters to search
    std::cout << "Testing search functionality" << std::endl;
    menu.addLetterToSearch('p');
    menu.displayMainMenu(); // Expect to find "Pasta" or "Pizza" based on search

    // Test resetting search
    std::cout << "Testing resetSearch" << std::endl;
    menu.resetSearch();
    menu.displayMainMenu(); // Search should be cleared

    // Test displaying a long line of text
    std::cout << "Testing long line wrapping" << std::endl;
    std::string long_line = "This is a very long line that should wrap when it exceeds the width of the console window.";
    menu.printLineLeftJustified(long_line, 0);

    std::cout << "All tests completed." << std::endl;
}

