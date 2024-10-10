#include "./Menu.h"
#include <iostream>
#include <random>
#include <chrono>



Menu::Menu()
{
    Console::Init();
    Console::SetTitle("CFOOD2");
    DisplaySplash();
}

void Menu::DisplaySplash()
{
    SHORT padding = (Console::getWidth() - 74) / 2;
    Console::SetIndent(padding);
    Console::SetAttribute(FOREGROUND_BLUE);
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
    Console::PutString(splash);
    Console::Print();
    Sleep(1500);
    Console::SetIndent(0);
    Console::SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);
    Console::Clear();
}

bool Menu::updateScreenSize()
{

    cols = Console::getWidth();
    rows = Console::getHeight();


    return true;

}
// todo: there must be a better way
uint32_t Menu::printLineLeftJustified(std::string line, uint32_t indent=0)
{
    if (line.size() < cols)
    {
        printIndent(indent);
        Console::PutStringLn(line);
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
            Console::PutStringLn(line.substr(base_index, span));

            return rows_printed;
        }

        if (span >= (uint32_t)cols - 1)
        {
            if (last_white_space_offset != 0)
            {
                printIndent(indent);
                Console::PutStringLn(line.substr(base_index, last_white_space_offset));

                base_index += last_white_space_offset;
                span = 0;
                rows_printed++;
            }
            else
            {
                printIndent(indent);
                Console::PutStringLn("-"+line.substr(base_index, span));

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

uint32_t Menu::getLineLength(std::string line, uint32_t indent = 0)
{
    if (line.size() < cols)
    {
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
            return rows_printed;
        }

        if (span >= (uint32_t)cols - 1)
        {
            if (last_white_space_offset != 0)
            {
                base_index += last_white_space_offset;
                span = 0;
                rows_printed++;
            }
            else
            {
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
        Console::PutChar(' ');
    }
}


void Menu::displayMainMenu()
{
    Console::UpdateScreenSize();
    updateScreenSize();

    if (displayTooSmall())
    {
        return;
    }

    Console::Clear();
    Console::SetAttribute(BACKGROUND_BLUE | FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    Console::PutStringLn("Recipes:");
    Console::SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);

    if (substring_to_search.size() == 0)
    {
        Console::PutChar('\n');
    }
    else
    {
        Console::PutStringLn("Search: " + substring_to_search);
    }
    Console::SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);
    Console::PutString(std::string(cols, '-'));

    uint32_t i = topRow;
    while(i < (uint32_t)(topRow + rows - LINES_RESERVED) && i < filteredList->size())
    {
        if (i == cursor)
        {
            Console::SetAttribute(BACKGROUND_BLUE | FOREGROUND_WHITE);
            printLineLeftJustified("> " + filteredList->at(i)->title, 2);
            Console::SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);

        }
        else 
        {
            printLineLeftJustified(filteredList->at(i)->title, 4);
        }
        i++;
    }
    Console::PutChar('\n');
    Console::SetAttribute(BACKGROUND_WHITE | FOREGROUND_BLACK);
    Console::SetCursorPosition(0, rows-1);
    Console::PutStringLn("[UP/DOWN] navigate | [ENTER] select | [BS] back | [ESC] exit | [TAB] surprise!");
    Console::SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);
    Console::Print();
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
    if (cursor == filteredList->size())
    {
        return;
    }

    // case 1: cursor is not at bottom
    cursor += cursor != filteredList->size() - 1 ? 1 : 0;

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
   
    recipeToDisplay = filteredList->at(cursor);
   
}

void Menu::addLetterToSearch(char c)
{
    substring_to_search.push_back(c);
    uint32_t index = Util::search_recipe_list(filteredList, substring_to_search);
    
    filteredList = Util::filterRecipes(filteredList, substring_to_search);
    
    if (index == -1)
    {
        return;
    }
    cursor = index;

}

void Menu::resetSearch()
{
    substring_to_search.clear();
    displayMainMenu();
}

void Menu::resetFilteredList()
{

    filteredList = Util::copyRecipeList(recipesList);
}



void Menu::mainMenuCallBack(int vk)
{
    int VK_A = 0x41;
    int VK_Z = 0x5A;
    //int VK_S = 0x53;
    auto recipe_callback = [this](int value) {
        this->recipeMenuCallBack(value);
    };

    try {
        switch (vk) {
        case(INVALIDATED_DISPLAY):
            displayMainMenu();
            break;
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
            recipe_page_on = 0;
            EventListener::setCallback(recipe_callback);
            displayRecipe();
            break;
        case (VK_BACK):
            resetSearch();
            resetFilteredList();
            displayMainMenu();
            break;
        case (VK_TAB): 
            if (!filteredList->empty()) {
               
                unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
                std::mt19937 gen(seed);  
                std::uniform_int_distribution<> dis(0, static_cast<int>(filteredList->size()) - 1);

                try {
                   
                    uint32_t randomIndex = dis(gen);
                    cursor = randomIndex;  
                    displayMainMenu();
                    selectRecipe();
                    EventListener::setCallback(recipe_callback);
                    displayRecipe();
                }
                catch (const std::exception) {
             
                    resetFilteredList();
                    cursor = 0;
                    displayMainMenu();
                }
            }
            else {
              
                resetFilteredList();
                cursor = 0;
                displayMainMenu();
            }
            break;



        default:
            if (VK_A <= vk && vk <= VK_Z)
            {
                addLetterToSearch(vk - VK_A + 'a');
                displayMainMenu();
            }
            else if (vk == VK_SPACE)
            {
                addLetterToSearch(' ');
                displayMainMenu();
            }
            break;
        }
    }
    catch (const std::out_of_range) {
        resetFilteredList();
        displayMainMenu();
        cursor = 0;  
    }
    catch (const std::exception) {
        //resetFilteredList();
        displayMainMenu();
        cursor = 0;
    }
    
}




void Menu::recipeMenuCallBack(int vk)
{
    auto callback = [this](int value) {
        mainMenuCallBack(value);
    };

    if (vk == INVALIDATED_DISPLAY)
    {
        displayRecipe();
    }

    if (vk == VK_BACK)
    {
        EventListener::setCallback(callback);
        displayMainMenu();

    }

    if (vk == VK_LEFT)
    {
        recipe_page_on -= (recipe_page_on > 0) ? 1 : 0;
        displayRecipe();
    }

    if (vk == VK_RIGHT)
    {
        recipe_page_on += 1;
        displayRecipe();
    }
    return;
}

void Menu::displayRecipe()
{
    updateScreenSize();
    Console::Clear();

    if (displayTooSmall())
    {
        return;
    }

    if (!recipeToDisplay)
    {
        return;
    }



    SHORT no_lines_printed = 0;
    SHORT on_page = 0;

    std::vector<std::string> recipe = recipeToDisplay->toStringArray();

    for (uint32_t i = 0; i < recipe.size(); i++)
    {
        std::string line = recipe.at(i);

        no_lines_printed += getLineLength(line);
        if (no_lines_printed + LINES_RESERVED > rows)
        {
            on_page += 1;
            no_lines_printed = 0;
            i -= (i > 6) ? 5 : 0;
        } else if (on_page == recipe_page_on)
        {
            printLineLeftJustified(line, 0);
        }
    }

    Console::SetAttribute(BACKGROUND_WHITE | FOREGROUND_BLACK);
    Console::SetCursorPosition(0, rows - 1);
    Console::PutStringLn("[LEFT/RIGHT] navigate | [RETURN] back | [ESC] exit");
    Console::SetAttribute(BACKGROUND_BLACK | FOREGROUND_WHITE);
    
    Console::Print();

}

bool Menu::displayTooSmall()
{

    if (cols < 25 || rows < 25)
    {
        Console::Clear();
        if (console->getWidth() * console->getHeight() > 20)
        {
            Console::PutStringLn("Display too small!");
            Console::Print();
        }
        return true;
    }
    return false;
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

