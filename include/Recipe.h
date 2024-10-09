/**
 * @file Recipe.h
 * @brief This file contains the definition of the Recipe class, 
 * which is responsible for organizing recipe files in a standard format.
 * 
 *
 */
#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <unordered_map>

/**
 * @brief The Recipe class represents a recipe with ingredients, instructions, and other metadata such as servings and title.
 * It provides functionality for adding ingredients, instructions, and managing measurements.
 */
class Recipe
{
public:
	/**
     * @brief Runs unit tests for the Recipe class.
     */
	static void unittest();
	
    /**
     * @brief Enum representing various units of measurement for ingredients.
     */
    enum Measurement_e {
        other,          /**< Represents an unspecified measurement. */
        teaspoon,       /**< Measurement in teaspoons. */
        tablespoon,     /**< Measurement in tablespoons. */
        fluid_ounce,    /**< Measurement in fluid ounces. */
        cup,            /**< Measurement in cups. */
        pint,           /**< Measurement in pints. */
        quarts,         /**< Measurement in quarts. */
        gallon,         /**< Measurement in gallons. */
        ounce,          /**< Measurement in ounces. */
        pound,          /**< Measurement in pounds. */
        gram,           /**< Measurement in grams. */
        kilogram        /**< Measurement in kilograms. */
    };

    /**
     * @brief Structure representing an ingredient, including its quantity, measurement unit, and name.
     */
    struct Ingredient {
        uint32_t value;             /**< The quantity of the ingredient. */
        Measurement_e measurement;  /**< The unit of measurement for the ingredient. */
        std::string ingredient;     /**< The name of the ingredient. */
    };

    bool isSaved;                   /**< Flag indicating whether the recipe has been saved to a file. */

    std::string filename;           /**< The filename where the recipe is stored. */
    void setFilename(std::string filename);
    std::string title;
   // std::string title;              /**< The title of the recipe. */
    void setTitle(std::string title);   
   
    std::vector<std::string> tags;    /**< The tags of the recipe. */
    void setTags(std::vector<std::string> tags);
    void addTag(std::string tag);

    uint32_t servings;              /**< The number of servings the recipe yields. */

    std::vector<Ingredient> ingredients; /**< A vector storing the ingredients for the recipe. */
    void addIngredient(uint32_t value, Measurement_e measurement, std::string ingredientName);

    std::vector<std::string> instructions; /**< A vector storing the instructions for the recipe. */
    void addInstruction(std::string instruction);
    void addInstructionAt(std::string instruction, uint32_t position);

    std::string remarks;            /**< Additional remarks or notes about the recipe. */
    void setRemarks(std::string remark);

    /**
     * @brief Default constructor for the Recipe class.
     */
    Recipe();

    /**
     * @brief Converts a string to the corresponding Measurement_e enumeration.
     * 
     * @param str The string representing the measurement.
     * @return The corresponding Measurement_e value.
     */
    static Measurement_e stringToMeasurement(std::string str);

    /**
     * @brief Converts a Measurement_e enumeration value to its string representation.
     * 
     * @param measurement The Measurement_e value.
     * @return The corresponding string representation.
     */
    static std::string measurementToString(Measurement_e measurement);

    /**
     * @brief Displays the recipe details, including ingredients, instructions, and title.
     */
    void Display();

    /**
     * @brief Converts the recipe to a string representation.
     * 
     * @return A string containing the recipe details.
     */
    std::string toString();

    /**
     * @brief Converts the recipe to a vector of strings, with each element representing a portion of the recipe.
     * 
     * @return A vector of strings representing the recipe.
     */
    std::vector<std::string> toStringArray();

private:
    /**
     * @brief Displays the details of a single ingredient.
     * 
     * @param ingredient The ingredient to be displayed.
     */
    void DisplayIngredient(struct Ingredient ingredient);

};


