#include "Recipe.h"

Recipe::Recipe() 
{
	title = "";
	servings = 0;
	remarks = "";

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

void Recipe::setRemarks(std::string remark)
{
	remarks = remark;
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