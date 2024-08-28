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

	bool isSaved;

	std::string filename;
	void setFilename(std::string filename);
	
	std::string title;
	void setTitle(std::string title);
	
	uint32_t servings;
	
	std::vector<Ingredient> ingredients;
	void addIngredient(uint32_t value, Measurement_e measurement, std::string ingredientName);
	
	
	std::vector<std::string> instructions;
	void addInstruction(std::string instruction);
	void addInstructionAt(std::string instruction, uint32_t position);
	void setInstructionAt(std::string instruction, uint32_t
		position);

	std::string remarks;
	void setRemarks(std::string remark);

	Recipe();

	static Measurement_e stringToMeasurement(std::string str);
	static std::string measurementToString(Measurement_e measurement);

	void Display();
	std::string toString();

	std::vector<std::string> toStringArray();
private:
	void DisplayIngredient(struct Ingredient ingredient);
};

