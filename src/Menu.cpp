#include "./Menu.h"

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

    uint32_t LINES_RESERVED = 2;
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

void Menu::mainMenuCallBack(int vk)
{
    switch (vk) {
    case (VK_UP):
        cursorUp();
        displayMainMenu();
        break;
    case (VK_DOWN):
        cursorDown();
        displayMainMenu();
        break;
    case (VK_RETURN):
        selectRecipe();
        auto callback = [this](int value) {
            this->recipeMenuCallBack(value);
        };
        EventListener::setCallback(callback);
        displayRecipe();
        break;

    }

}

void Menu::recipeMenuCallBack(int vk)
{
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