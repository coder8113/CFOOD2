#include "./Parser.h"

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
 *
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
	printf("\n\n\n\n");
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
