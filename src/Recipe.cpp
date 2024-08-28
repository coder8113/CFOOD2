#include "./Recipe.h"

Recipe::Recipe() 
{
	title = "";
	filename = "";
	isSaved = true;
	servings = 0;
	remarks = "";

}

void Recipe::setFilename(std::string filename)
{
	this->filename = filename;
	this->isSaved = false;
}

void Recipe::Display()
{
	printf("%s\n", title.c_str());

	printf("\nIngredients: \n");

	for (Ingredient ingredient : ingredients)
	{
		DisplayIngredient(ingredient);
	}

	printf("\nInstructions: \n");

	int i = 1;
	for (std::string instruction : instructions)
	{
		printf("\t%d. %s\n", i, instruction.c_str());
		i++;
	}

	printf("\nRemarks: \n");
	
	if (!remarks.empty()) {
		printf("%s\n", remarks.c_str());
	}

}

void Recipe::DisplayIngredient(struct Ingredient ingredient)
{
	if (ingredient.measurement == other) {
		printf("\t%s\n", ingredient.ingredient.c_str());
	}
	else 
	{
		printf("\t%d %s %s \n", ingredient.value, measurementToString(ingredient.measurement).c_str(), ingredient.ingredient.c_str());
	}
}

void Recipe::setTitle(std::string title)
{
	this->title = title;
	this->isSaved = false;
}

void Recipe::addIngredient(uint32_t value, Measurement_e measurement, std::string ingredientName)
{
	Ingredient newIngredient
	{
		value, measurement, ingredientName
	};

	ingredients.push_back(newIngredient);
}

void Recipe::addInstruction(std::string instruction)
{
	instructions.push_back(instruction);
}

void Recipe::addInstructionAt(std::string instruction, uint32_t position)
{
	if (position > this->instructions.size())
	{
		this->instructions.push_back(instruction);
	}

	if (position < 0)
	{
		return;
	}

	this->instructions.insert(
		this->instructions.begin() + position,
		instruction);

}

void Recipe::setInstructionAt(std::string instruction, uint32_t position)
{
	return;
}

void Recipe::setRemarks(std::string remark)
{
	remarks = remark;
	this->isSaved = false;
}

Recipe::Measurement_e Recipe::stringToMeasurement(std::string str)
{
	static const std::unordered_map<std::string, Measurement_e> measurementMap = {
		{"teaspoon", teaspoon},
		{"tsp", teaspoon},
		{"tablespoon", tablespoon},
		{"tbsp", tablespoon},
		{"t", tablespoon},
		{"fl oz", fluid_ounce},
		{"fluid oz", fluid_ounce},
		{"fluid ounce", fluid_ounce},
		{"cup", cup},
		{"cups", cup},
		{"cup(s)", cup},
		{"c", cup},
		{"pint", pint},
		{"quart", quarts},
		{"qt", quarts},
		{"gallon", gallon},
		{"gal", gallon},
		{"ounce", ounce},
		{"oz", ounce},
		{"pound", pound},
		{"lb", pound},
		{"gram", gram},
		{"g", gram},
		{"kilogram", kilogram},
		{"kg", kilogram}
	};


	auto it = measurementMap.find(str);
	if (it != measurementMap.end()) {
		return it->second;
	}
	return other; // Return a default or error value

	return Recipe::other;
}

std::string Recipe::measurementToString(Recipe::Measurement_e measurement)
{
	static const std::unordered_map<Recipe::Measurement_e, std::string> measurementMap = {
		{teaspoon, "tsp"},
		{tablespoon, "tbsp"},
		{fluid_ounce, "fl oz"},
		{cup, "cup"},
		{pint, "pt"},
		{quarts, "qt"},
		{gallon, "gal"},
		{ounce, "oz"},
		{pound, "lb"},
		{gram, "g"},
		{kilogram, "kg"},
		{other, "other"} // Default or unspecified measurement
	};

	auto it = measurementMap.find(measurement);
	if (it != measurementMap.end()) {
		return it->second;
	}
	return "other"; // Return a default or error value
}

std::string Recipe::toString()
{
	std::string result = "";
	
	// title
	result += "# ";
	result += title;
	result += "\n";

	// ingredients
	result += "## Ingredients\n";

	for (Ingredient ingredient : ingredients)
	{
		result += "* ";
		if (ingredient.measurement == other)
		{
			result += ingredient.ingredient;
		}
		else
		{
			result += std::to_string(ingredient.value);
			result += measurementToString(ingredient.measurement);
			result += " ";
			result += ingredient.ingredient;
		}
		result += "\n";
		
	}

	// instructions
	result += "## Instructions\n";

	int i = 1;
	for (std::string instruction : instructions)
	{
		result += std::to_string(i);
		result += ". ";
		result += instruction;
		result += "\n";
		i++;
	}

	result += "## Remarks\n";
	result += remarks;
	return result;
}

std::vector<std::string> Recipe::toStringArray()
{
	std::vector<std::string> result;

	// title
	result.push_back(title+"\n");

	// ingredients
	result.push_back("Ingredients \n");

	for (Ingredient ingredient : ingredients)
	{
		if (ingredient.measurement == other)
		{
			result.push_back("  " + ingredient.ingredient);
		}
		else
		{
			std::string ingredientName = "  ";
			ingredientName += std::to_string(ingredient.value);
			ingredientName += measurementToString(ingredient.measurement);
			ingredientName += " ";
			ingredientName += ingredient.ingredient;
			result.push_back(ingredientName);
		}

	}

	// instructions
	result.push_back("\nInstructions\n");

	int i = 1;
	for (std::string instruction : instructions)
	{
		std::string newStr = "  ";
		newStr += std::to_string(i);
		newStr += ". ";
		newStr += instruction;
		result.push_back(newStr);
		i++;
	}

	if (!remarks.empty())
	{
		result.push_back("\nRemarks\n");
		result.push_back(remarks);

	}
	return result;
}



