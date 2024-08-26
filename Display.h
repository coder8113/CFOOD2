#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <Windows.h>
#include <cstdlib>
#include <iostream>

class Display
{
	Display();
	


	std::vector<std::string> buffer;
	// window
	uint32_t width;
	uint32_t height;

	uint32_t top_row_index;

	uint32_t cursor;

	void verticalScroll(uint32_t amountDown);

	void display();

	// update screen size as given to us by OS.
	void updateScreenSize();

};

