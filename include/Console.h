/**
* @file Console.h
* @brief Console is responsible for interacting with the console api
* of win32. It handles buffer allocation, reallocation, and writing.
* 
* 
*/


#pragma once

#include <windows.h>
#include <string>
#include <iostream>
#include <cassert>

// Background Color Definitions
#define BACKGROUND_BLACK (0)
#define BACKGROUND_MAGENTA (BACKGROUND_BLUE | BACKGROUND_RED)
#define BACKGROUND_YELLOW (BACKGROUND_GREEN | BACKGROUND_RED)
#define BACKGROUND_CYAN (BACKGROUND_GREEN | BACKGROUND_BLUE)
#define BACKGROUND_WHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)

// Foreground Color Definitions
#define FOREGROUND_BLACK (0)
#define FOREGROUND_MAGENTA (FOREGROUND_BLUE | FOREGROUND_RED)
#define FOREGROUND_YELLOW (FOREGROUND_GREEN | FOREGROUND_RED)
#define FOREGROUND_CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// 

class Console
{
public:

	static void unittest();

	/*!
	* Initialize the Console. Sets the member variables of this class.
	*/	
	static void Init();

	/*!
	* Gets the current screen size, and resizes the buffer as appropriate.
	*/
	static void UpdateScreenSize();
	
	/*!
	* Writes the buffer to the console output and resets cursor.
	*/
	static void Print();

	/*!
	* Write a character to the buffer with the current attribute. 
	* If newline, will write spaces until reaches the end of the
	* current row.
	* @param ch Character to write.
	*/
	static void PutChar(CHAR ch);

	/*!
	* Write a characters to the buffer with the current attribute.
	* If newline, will write spaces until reaches the end of the
	* current row.
	* @param ch Characters to write
	* @param size Number of characters to write.
	*/
	static void PutChars(CHAR* ch, size_t size);
	
	/*!
	* Write a characters to the buffer with the current attribute.
	* If newline, will write spaces until reaches the end of the
	* current row.
	* @param ch Characters to write
	* @param size Number of characters to write.
	*/
	static void PutChars(const CHAR* ch, size_t size);
	
	/*!
	* Write an std::string to the buffer with the current attribute.
	* If newline, will write spaces until reaches the end of the
	* current row.
	* @param s Characters to write
	*/
	static void PutString(std::string s);
	
	/*!
	* Write an std::string to the buffer and appends newline with 
	* the current attribute.
	* If newline, will write spaces until reaches the end of the
	* current row.
	* 
	* @param s Characters to write
	*/
	static void PutStringLn(std::string s);

	/*!
	* Set the cursor position which dictates where we are writing
	* to the buffer
	* @param x x position
	* @param y y position
	*/
	static void SetCursorPosition(SHORT x, SHORT y);
	
	/*!
	* Sets the entire buffer to white space.
	*/
	static void Clear();

	/*!
	* Sets the title of our application.
	* @param title title of app
	*/
	static void SetTitle(LPCSTR title);

	/*!
	* Set the attribute of the next written character.
	* @param attribute colour of foreground, background
	*/
	static void SetAttribute(WORD attribute);
	
	/*!
	* Sets the x position of where we start writing after ending
	* a row.
	* @param i indent
	*/
	static void SetIndent(SHORT i);

	/*!
	* Get width of console in characters
	* @return width of console
	*/
	static SHORT getWidth() { return width;  }
	
	/*!
	* Get height of console in characters
	* @return height of console
	*/
	static SHORT getHeight() { return height;  }

private:
	static HANDLE hConsole;
	
	static CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	
	static size_t buffer_size;
	static CHAR_INFO* buffer;
	
	
	static COORD cursor;
	static WORD attributes;
	static SHORT width;
	static SHORT height;
	static SHORT indent;
};