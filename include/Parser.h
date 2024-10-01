/**
 * @file Parser.h
 * @brief This file contains the definition of the Parser class, which is responsible for parsing recipe files.
 * 
 * The Parser class combines various helper parsing functions to process different sections of a recipe 
 * and populates a Recipe object.
 */
#pragma once

#include <string>
#include <cstdint>
#include <cctype>
#include "Recipe.h"

/**
 * @brief Parses the entire recipe file.
 * 
 * This class handles parsing data from a recipe file, and stores the information in a Recipe object.
 */
class Parser
{
public:
	/**
     * @brief Runs unit tests for the Menu class.
     */
	static void unittest();
	/**
	 * @brief Struct to hold data, position, and span information for parsing.
	 */
	struct span_s {
		std::string data;     ///< The raw data being parsed.
		uint64_t position;    ///< The current position in the data.
		uint64_t span;        ///< The span of the current segment being parsed.
	};

	/**
	 * @brief Enum representing the different states of parsing.
	 */
	enum state_e {
		INIT_MODE,          ///< Initial state before parsing begins.
		TITLE_MODE,         ///< Parsing the title of the recipe.
		TAGS_MODE,          ///< Parsing the tags of the recipe
		INGREDIENTS_MODE,   ///< Parsing the ingredients of the recipe.
		INSTRUCTIONS_MODE,  ///< Parsing the instructions of the recipe.
		REMARKS_MODE,       ///< Parsing the remarks section of the recipe.
	};

	struct span_s m_Span;  ///< The span structure used for tracking the parsing progress.
	enum state_e m_State;  ///< The current state of parsing.
	Recipe* recipe;        ///< Pointer to the Recipe object being populated.

	/**
	 * @brief Constructs a new Parser object.
	 * 
	 * @param data The data to be parsed.
	 * @param filename The name of the recipe file.
	 */
	Parser(std::string data, std::string filename);

	/**
	 * @brief Parses the recipe file.
	 * 
	 * Combines various helper functions to extract all relevant sections of the recipe file.
	 */
	void Parse();

	/**
	 * @brief Returns the Recipe object after parsing.
	 * 
	 * @return Recipe* Pointer to the populated Recipe object.
	 */
	Recipe* getReceipe();

	// Public constants for identifying sections in the recipe file
	std::string INGREDIENTS = "Ingredients"; ///< Constant for ingredients section identifier.
	std::string INSTRUCTIONS = "Instructions"; ///< Constant for instructions section identifier.
	std::string REMARKS = "Remarks"; ///< Constant for remarks section identifier.
	std::string TAGS = "Tags"; ///< Constant for tags section identifier


private:

	/**
	 * @brief Parses the heading of the recipe.
	 */
	void parseHeading();

	/**
	 * @brief Parses the tags of the recipe.
	 */
	void parseTags();


	/**
	 * @brief Parses bullet points in the recipe.
	 */
	void parseBulletPoint();

	/**
	 * @brief Parses lists in the recipe.
	 */
	void parseList();

	/**
	 * @brief Parses individual ingredients in the recipe.
	 */
	void parseIngredient();

	/**
	 * @brief Peeks at the next character in the data without advancing the position.
	 * 
	 * @return char The next character in the data.
	 */
	char peekChar();

	/**
	 * @brief Advances the position in the data by a specified amount.
	 * 
	 * @param amount The amount to advance (default is 1).
	 * @return true If the position was successfully advanced.
	 * @return false If advancing went beyond the data length.
	 */
	bool advance(uint64_t amount=1);

	/**
	 * @brief Pops and returns the next segment of data.
	 * 
	 * @return std::string The next segment of data.
	 */
	std::string pop();

	std::string trim(const std::string& str);
	
};
