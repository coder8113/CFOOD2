#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <unordered_map>

class Recipe
{
public:

	enum Measurement_e {
		other,
		teaspoon,
		tablespoon,
		fluid_ounce,
		cup,
		pint,
		quarts,
		gallon,
		ounce,
		pound,
		gram,
		kilogram

	};


	struct Ingredient {
		uint32_t value;
		Measurement_e measurement;
		std::string ingredient;
	};

	std::string title;
	uint32_t servings;
	std::vector<Ingredient> ingredients;
	std::vector<std::string> instructions;
	std::string remarks;

	Recipe();

	Measurement_e stringToMeasurement(std::string str);
	std::string measurementToString(Measurement_e measurement);


	void Display();
	void setTitle(std::string title);
	void addIngredient(uint32_t value, Measurement_e measurement, std::string ingredientName);
	void addInstruction(std::string instruction);
	void setRemarks(std::string remark);
private:
	void DisplayIngredient(struct Ingredient ingredient);
};

