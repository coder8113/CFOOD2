#pragma once

#include <windows.h>
#include <string>

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
	Console();
	~Console();

	void UpdateScreenSize();
	void Print();
	void PutChar(CHAR ch);
	void PutChars(CHAR* ch, size_t size);
	void PutChars(const CHAR* ch, size_t size);
	void PutString(std::string s);
	void PutStringLn(std::string s);

	void SetCursorPosition(SHORT x, SHORT y);
	void Clear();
	void SetTitle(LPCSTR title);
	void SetAttribute(WORD attribute);
	void SetIndent(SHORT i);

	SHORT getWidth() { return width;  }
	SHORT getHeight() { return height;  }

private:
	HANDLE hConsole;
	
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	
	size_t buffer_size;
	CHAR_INFO* buffer;
	
	
	COORD cursor;
	WORD attributes;
	SHORT width;
	SHORT height;
	SHORT indent;
};