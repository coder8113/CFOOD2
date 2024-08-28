/**
 * @file file.h
 * @brief This file is a utility class which contains file management functions
 * It interacts with the filesystem to load, save, list, and delete files, providing 
 * essential functionality for applications dealing with recipes or other data stored in files.
 */
#pragma once

#include <string>
#include <vector>
#include <stdbool.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <wchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <locale>
#include <cstdio>
#include <codecvt>

#include "Recipe.h"
#include "Parser.h"

/**
 * @brief The file class provides static methods for file and directory operations,
 * such as listing directory contents, loading and saving recipes, and handling file conversions.
 */
class file
{
public:
    /**
     * @brief Lists the contents of a directory and stores them in a provided vector.
     * 
     * @param fileTable A pointer to a vector where the file names will be stored.
     * @param sDir The directory path to list the contents of.
     * @return True if the directory contents were successfully listed, false otherwise.
     */
    static bool ListDirectoryContents(std::vector<wchar_t*> *fileTable, const wchar_t *sDir);

    /**
     * @brief Loads all recipe files from a specified directory.
     * 
     * @param sDir The directory from which to load all recipes.
     * @return A vector of pointers to Recipe objects that were loaded from the directory.
     */
    static std::vector<Recipe*> loadAllRecipes(const wchar_t *sDir);

    /**
     * @brief Loads the content of a specified file into a string.
     * 
     * @param fileName The name of the file to load.
     * @return A string containing the contents of the file.
     */
    static std::string LoadFile(const wchar_t* fileName);

    /**
     * @brief Saves a recipe to a file.
     * 
     * @param recipe A pointer to the Recipe object to be saved.
     * @return True if the recipe was successfully saved, false otherwise.
     */
    static bool saveRecipeToFile(Recipe* recipe);

    /**
     * @brief Deletes a specified file from the file system.
     * 
     * @param filename The name of the file to delete.
     * @return True if the file was successfully deleted, false otherwise.
     */
    static bool deleteFile(std::string filename);

private:
    /**
     * @brief Converts a wide-character string (wchar_t*) to a standard string.
     * 
     * @param wstr The wide-character string to convert.
     * @return A standard string containing the converted characters.
     */
    static std::string wcharToString(const wchar_t* wstr);
};
