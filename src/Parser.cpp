#include "./Parser.h"
#include <iostream>
#include <cassert>
#include <string>
#include <file.h>

Parser::Parser(std::string data, std::string filename) {
	m_Span.data = data;
	m_Span.position = 0;
	m_Span.span = 0;
	m_State = INIT_MODE;
	recipe = new Recipe();
	recipe->setFilename(filename);
}

Recipe* Parser::getReceipe()
{
	return recipe;
}

/**
 * @brief Parses the entire recipe file
 * 
 * This function parses all of the data contained in a recipe file, by combining the 
 * different helper parsing functions.
 * TODO: Inifinit loop needs to be fixed.
 */
void Parser::Parse()
{
	while (m_Span.position + m_Span.span < m_Span.data.length()) {
		if (peekChar() == '#') 
		{
			m_State = TITLE_MODE;
			parseHeading();
		}

		if (peekChar() == '*')
		{
			parseBulletPoint();
		}

		if (isdigit(peekChar()))
		{
			parseList();
		}



		if (peekChar() == '\n')
		{
			// eol
		}
		advance();
	}
}

/**
 * @brief Adds two numbers.
 * 
 * This function adds two integer numbers and returns the result.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return int Sum of a and b.
 */
void Parser::parseHeading()
{
	advance();

	if (peekChar() == '#') {
		advance(2);
		pop();
		while (peekChar() != '\n') {
			advance(1);

		}
		std::string subheading = pop();

		if (subheading == INGREDIENTS)
		{
			m_State = INGREDIENTS_MODE;
			//printf("<subheading> ingredients\n");
		}
		if (subheading == INSTRUCTIONS)
		{
			m_State = INSTRUCTIONS_MODE;
			//printf("<subheading> instructions;\n");
		}
		if (subheading == REMARKS)
		{
			m_State = REMARKS_MODE;
			//printf("<subheading> remarks\n");
		}
		if (subheading == TAGS) {
			m_State = TAGS_MODE;
		}
		return;

	}

	// We have a Title
	// Removing white space.
	while (peekChar() == ' ')
	{
		advance();
	}
	pop();

	// Extracting title
	while (peekChar() != '\n') 
	{
		advance();
	}
	std::string title = pop();
	//printf("<title> %s\n", title.c_str());
	recipe->setTitle(title);

}

// <bullet-point> -> * <alphanumeric>
void Parser::parseBulletPoint() 
{
	advance();
	while (peekChar() == ' ')
	{
		advance();
	}
	pop();
	parseIngredient();
}

void Parser::parseIngredient()
{
	// if we see something that is not in the form
	// <value> <unit> <ingredient>
	// we will then back track to this and continue passing.
	uint64_t initPos = m_Span.position;
	uint64_t initSpan = m_Span.span; 

	int value = -1;
	// if we have an ingredient in the form of:
	// <value> <unit> <ingredient>
	if (isdigit(peekChar()))
	{
		// value
		while (isdigit(peekChar()) && peekChar() != '\n')
		{
			advance();
		}
		std::string strVal = pop();
		value = std::stoi(strVal);
		// whitespace
		while (peekChar() == ' ')
		{
			advance();
		}
		pop();
		// unit
		while (isalpha(peekChar()))
		{
			advance();
		}
		std::string unit = pop();
		//whitespace
		while (peekChar() == ' ')
		{
			advance();
		}
		pop();
		//ingredient
		while (peekChar() != '\n')
		{
			advance();
		}
		std::string ingredient = pop();

		for (char& c : unit) {
			c = std::tolower(static_cast<unsigned char>(c));
		}
		// USE STDMAP INSTEAD
		Recipe::Measurement_e internalUnit = Recipe::stringToMeasurement(unit);

		if (internalUnit != Recipe::other) {
			//printf("<INGREDIENT> <val> %d, <unit> %s, <desc> %s\n", value, unit.c_str(), ingredient.c_str());
			recipe->addIngredient(value, internalUnit, ingredient);

			return;
		}
		else {
			m_Span.position = initPos;
			m_Span.span = initSpan;
		}
	}


	while (peekChar() != '\n')
	{
		if (peekChar())
		advance();
	}
	std::string bulletPoint = pop();
	//printf("<ingredient> %s \n", bulletPoint.c_str());
	if (m_State == INGREDIENTS_MODE)
	{
		recipe->addIngredient(-1, Recipe::other, bulletPoint);
	}
}

// <list> -> <digit> | <digit>.
// <digit> -> <digit> | 0123456789
void Parser::parseList()
{
	pop();
	while (isdigit(peekChar()))
	{
		advance();
	}
	std::string digit = pop();

	while (!isalpha(peekChar()))
	{
		advance();
	}
	pop();

	while (peekChar() != '\n')
	{
		advance();
	}
	std::string line = pop();

	//printf("<list> %s %s\n", digit.c_str(), line.c_str());
	if (m_State == INSTRUCTIONS_MODE)
	{
		recipe->addInstruction(line);
	}

}

void Parser::parseTags()
{
	advance();
	std::string tagsLine;

	while (peekChar() != '\n') {
		advance();
	}
	tagsLine = pop();

	std::vector<std::string> tags;
	size_t start = 0, end = 0;
	while ((end = tagsLine.find(',', start)) != std::string::npos) {
		std::string tag = tagsLine.substr(start, end - start);
		tags.push_back(trim(tagsLine.substr(start)));

		recipe->setTags(tags);
	}
}

char Parser::peekChar() {
	return m_Span.data[m_Span.position + m_Span.span];
}

bool Parser::advance(uint64_t amount) {
	if (m_Span.position + m_Span.span < m_Span.data.length()) {
		m_Span.span+= amount;
		return true;
	}
	return false;
}

std::string Parser::pop() {
	std::string result = m_Span.data.substr(m_Span.position, m_Span.span);
	m_Span.position += m_Span.span;
	m_Span.span = 0;
	return result;
}

std::string Parser::trim(const std::string& str) {
	const char* whitespace = "\t\n\r\f\v";
	size_t start = str.find_first_not_of(whitespace);
	size_t end = str.find_last_not_of(whitespace);

	return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void Parser::unittest() {
	std::cout << "Testing parser" << std::endl;
	std::string test_data =
		"# TITLE\n"
		"## Ingredients\n"
		"* 200g test\n"
		"* 1 teaspoon test\n"
		"* 1 tablespoon test\n"
		"* 1 cup test\n"
		"* 1 pint test\n"
		"* 1 quart test \n"
		"* 1 gallon test \n"
		"* 1 ounce test \n"
		"* 1 pound test \n"
		"* 1 gram test\n"
		"* 1 kilogram test\n"
		"* 1 fl oz test\n"
		"## Instructions\n"
		"1. test_this\n"
		"## Remarks\n"
		"remark\n";

	Parser titleTest(test_data, "file");
	
	titleTest.Parse();
	Recipe* test_recipe = titleTest.getReceipe();
	assert(test_recipe->title == "TITLE");

	assert(test_recipe->ingredients.at(0).value = 200);
	assert(test_recipe->ingredients.at(0).measurement = Recipe::gram);
	assert(test_recipe->ingredients.at(0).ingredient == "test");

	std::cout << test_recipe->ingredients.size() << std::endl;
	
	std::cout << "Parse: teaspoon test." << std::endl;
	assert(test_recipe->ingredients.at(1).measurement == Recipe::teaspoon);
	std::cout << "Parse: tablespoon test." << std::endl;
	assert(test_recipe->ingredients.at(2).measurement == Recipe::tablespoon);
	std::cout << "Parse: cup test." << std::endl;
	assert(test_recipe->ingredients.at(3).measurement == Recipe::cup);
	std::cout << "Parse: pint test." << std::endl;
	assert(test_recipe->ingredients.at(4).measurement == Recipe::pint);
	std::cout << "Parse: quartz test." << std::endl;
	assert(test_recipe->ingredients.at(5).measurement == Recipe::quarts);
	std::cout << "Parse: gallon test." << std::endl;
	assert(test_recipe->ingredients.at(6).measurement == Recipe::gallon);
	std::cout << "Parse: ounce test." << std::endl;
	assert(test_recipe->ingredients.at(7).measurement == Recipe::ounce);
	std::cout << "Parse: pound test." << std::endl;
	assert(test_recipe->ingredients.at(8).measurement == Recipe::pound);
	std::cout << "Parse: gram test." << std::endl;
	assert(test_recipe->ingredients.at(9).measurement == Recipe::gram);
	std::cout << "Parse: kilogram test." << std::endl;
	assert(test_recipe->ingredients.at(10).measurement == Recipe::kilogram);


	std::cout << test_recipe->remarks << std::endl;
	assert(test_recipe->instructions[0] == "test_this");
	//assert(test_recipe->remarks == "remark"); // Remarks not yet implemented.

}