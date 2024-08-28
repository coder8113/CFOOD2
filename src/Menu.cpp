#include "./Menu.h"

void Menu::Display()
{

}

void Menu::setRecipes(std::vector<Recipe*>* recipeList)
{
    recipes = recipeList;
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
uint32_t Menu::printLine(std::string line)
{
    if (line.size() < cols)
    {
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
            printf("%s\n", line.substr(base_index, span).c_str());

            return rows_printed;
        }

        if (span >= cols - 1)
        {
            if (last_white_space_offset != 0)
            {
                printf("%s\n", line.substr(base_index, last_white_space_offset).c_str());

                base_index += last_white_space_offset;
                span = 0;
                rows_printed++;
            }
            else
            {
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