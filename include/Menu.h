/**
 * @file Menu.h
 * @brief This file contains the definition of the Menu class, 
 * which is responsible for the main program menu logic.
 * 
 *
 */
#pragma once

#include <cstdint>
#include <windows.h>
#include <cstdio>
#include <vector>
#include <functional>

#include "Recipe.h"
#include "EventListener.h"
#include "Util.h"

/**
 * @brief The Menu class is responsible for handling the display and interaction with a menu system,
 * including navigating recipes, searching, and updating the display.
 */
class Menu
{
public:
    /**
     * @brief Runs unit tests for the Menu class.
     */
    static void unittest();

    /**
     * @brief Displays the current menu or interface on the screen.
     */
    void Display();

    /**
     * @brief Prints the size of the menu or interface.
     */
    void printSize();

    /**
     * @brief Sets the list of recipes for the menu to display.
     * 
     * @param recipes A pointer to a vector of Recipe pointers.
     */
    void setRecipeList(std::vector<Recipe*>* recipes)
    {
        recipesList = recipes;
    }

    

    /**
     * @brief Displays the main menu of the program.
     */
    void displayMainMenu();

    /**
     * @brief Handles the callback for main menu input.
     * 
     * @param vk The virtual key code for the pressed key.
     */
    void mainMenuCallBack(int vk);

    /**
     * @brief Displays the current selected recipe.
     */
    void displayRecipe();

    /**
     * @brief Handles the callback for recipe menu input.
     * 
     * @param vk The virtual key code for the pressed key.
     */
    void recipeMenuCallBack(int vk);

    /**
     * @brief Adds a letter to the current search string.
     * 
     * @param c The character to add to the search string.
     */
    void addLetterToSearch(char c);

    /**
     * @brief Selects the currently highlighted recipe.
     */
    void selectRecipe();

    /**
     * @brief Moves the cursor up in the menu.
     */
    void cursorUp();

    /**
     * @brief Moves the cursor down in the menu.
     */
    void cursorDown();

    /**
     * @brief Resets the current search string.
     */
    void resetSearch();

    /**
     * @brief Prints a line left-justified with a given indent.
     * 
     * @param line The string to print.
     * @param indent The number of spaces to indent.
     * @return The length of the printed line.
     */
    uint32_t printLineLeftJustified(std::string line, uint32_t indent);

private:
    uint32_t rows = 0;        /**< The number of rows in the display. */
    uint32_t cols = 0;        /**< The number of columns in the display. */
    uint32_t topRow = 0;      /**< The top row currently displayed. */
    uint32_t cursor = 0;      /**< The current cursor position in the menu. */

    HWND window;              /**< The handle to the window. */
    HANDLE output_handle;     /**< The handle to the console output. */

    std::string substring_to_search;  /**< The search string being used for filtering recipes. */

    std::vector<Recipe*>* recipesList; /**< A pointer to the list of recipes available in the menu. */
    Recipe* recipeToDisplay = NULL;    /**< The currently selected recipe to display. */

    /**
     * @brief Prints the specified amount of indentation spaces.
     * 
     * @param indent The number of spaces to print.
     */
    void printIndent(uint32_t indent);

    /**
     * @brief Updates the screen size based on the current window dimensions.
     * 
     * @return True if the screen size was updated, false otherwise.
     */
    bool updateScreenSize();
};
