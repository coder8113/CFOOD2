#include "./Menu.h"
#include <iostream>

Menu::Menu()
{
    console = new Console();
    console->SetTitle("CFOOD2");
    DisplaySplash();
}

void Menu::DisplaySplash()
{
    SHORT padding = (console->getWidth() - 74) / 2;
    console->SetIndent(padding);
    console->SetAttribute(FOREGROUND_BLUE);
    std::string splash =
        "\n"
        " .d8888b.         8888888888 .d88888b.   .d88888b.  8888888b.   .d8888b.\n"
        "d88P  Y88b        888       d88P   Y88b d88P   Y88b 888   Y88b d88P  Y88b\n"
        "888    888        888       888     888 888     888 888    888        888\n"
        "888               8888888   888     888 888     888 888    888     .d88P\n"
        "888         8888  888       888     888 888     888 888    888 .od888P\n"
        "888    888        888       888     888 888     888 888    888  d88P\n"
        "Y88b  d88P        888       Y88b..d88P  Y88b..d88P  888.d88P   888\n"
        " Y8888P           888        Y88888P     Y88888P    888888P    888888888\n"
        "\n"
        "                  By Jennifer Puzey and Robert Cresswell                 \n"
        "         Special thanks to Boris Trifkovic for his contributions.        \n";
    console->PutString(splash);
    console->Print();
    Sleep(1500);
    console->SetIndent(0);
    console->SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);
    console->Clear();
}

bool Menu::updateScreenSize()
{

    cols = console->getWidth();
    rows = console->getHeight();


    return true;

}
// todo: there must be a better way
uint32_t Menu::printLineLeftJustified(std::string line, uint32_t indent=0)
{
    if (line.size() < cols)
    {
        printIndent(indent);
        console->PutStringLn(line);
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
            console->PutStringLn(line.substr(base_index, span));

            return rows_printed;
        }

        if (span >= cols - 1)
        {
            if (last_white_space_offset != 0)
            {
                printIndent(indent);
                console->PutStringLn(line.substr(base_index, last_white_space_offset));

                base_index += last_white_space_offset;
                span = 0;
                rows_printed++;
            }
            else
            {
                printIndent(indent);
                console->PutStringLn("-"+line.substr(base_index, span));

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
        console->PutChar(' ');
    }
}


void Menu::displayMainMenu()
{
    console->UpdateScreenSize();
    updateScreenSize();
    console->Clear();
    console->SetAttribute(BACKGROUND_BLUE | FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    console->PutStringLn("Recipes:");
    console->SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);

    if (substring_to_search.size() == 0)
    {
        console->PutChar('\n');
    }
    else
    {
        console->PutStringLn("Search: " + substring_to_search);
    }
    console->SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);
    console->PutString(std::string(cols, '-'));

    uint32_t i = topRow;
    while(i < topRow + rows - LINES_RESERVED && i < recipesList->size())
    {
        if (i == cursor)
        {
            console->SetAttribute(BACKGROUND_BLUE | FOREGROUND_WHITE);
            printLineLeftJustified("> " + recipesList->at(i)->title, 2);
            console->SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);

        }
        else 
        {
            printLineLeftJustified(recipesList->at(i)->title, 4);
        }
        i++;
    }
    console->PutChar('\n');
    console->SetAttribute(BACKGROUND_WHITE | FOREGROUND_BLACK);
    console->PutStringLn("[UP/DOWN] navigate | [ENTER] select | [ESC] exit");
    console->SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);
    console->Print();
}

void Menu::cursorUp()
{
    if (cursor == 0)
    {
        return;
    }
    cursor -= cursor != 0 ? 1 : 0;
    if (cursor == topRow && topRow != 0) {
        topRow--;
    }

    checkCursorOffscreen();
}

void Menu::cursorDown()
{
    // case 0: cursor is at bottom and cannot move list down.
    if (cursor == recipesList->size())
    {
        return;
    }

    // case 1: cursor is not at bottom
    cursor += cursor != recipesList->size() - 1 ? 1 : 0;

    // case 2: cursor is at bottom and can move list down.
    if (cursor >= (topRow + rows - LINES_RESERVED))
    {
        topRow++;
    }

    checkCursorOffscreen();

}

void Menu::checkCursorOffscreen()
{
    if (cursor < topRow || topRow + rows - LINES_RESERVED < cursor)
    {
        topRow = cursor;
    }
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
    console->Clear();
    if (!recipeToDisplay)
    {
        return;
    }

    std::vector<std::string> recipe = recipeToDisplay->toStringArray();

    for (std::string line : recipe)
    {
        printLineLeftJustified(line, 0);
    }
    console->Print();

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

