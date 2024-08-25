#pragma once

#include <string>
#include <cstdint>
#include <cctype>
#include "Recipe.h"

class Parser
{
public:
	struct span_s {
		std::string data;
		uint64_t position;
		uint64_t span;
	};

	enum state_e {
		INIT_MODE,
		TITLE_MODE,
		INGREDIENTS_MODE,
		INSTRUCTIONS_MODE,
		REMARKS_MODE,
	};

	struct span_s m_Span;
	enum state_e m_State;
	Recipe* recipe;

	Parser(std::string data);

	void Parse();
	Recipe* getReceipe();

	std::string INGREDIENTS = "Ingredients";
	std::string INSTRUCTIONS = "Instructions";
	std::string REMARKS = "Remarks";


private:

	void parseHeading();
	void parseBulletPoint();
	void parseList();
	void parseIngredient();
	char peekChar();
	bool advance(uint64_t amount=1);
	std::string pop();

};

