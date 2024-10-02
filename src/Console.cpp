#include "./Console.h"

Console::Console()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	UpdateScreenSize();
	buffer_size = width * height;
	buffer = (CHAR_INFO *)malloc(sizeof(CHAR_INFO) * width*height);

	attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	Clear();


}

Console::~Console()
{
	free(buffer);
	// I think this will only run when the application
	// is exiting so this isn't that important.

}

void Console::UpdateScreenSize()
{
	/* At this point, our process has a console window assigned to it */
	HWND window = GetConsoleWindow();
	auto output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	/* Grab the default size as given to us by the OS */
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;

	if (!GetConsoleScreenBufferInfo(output_handle, &buffer_info)) {
		return;
	}

	/* Don't show the console cursor */
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize = 1;
	cursor_info.bVisible = false;

	if (!SetConsoleCursorInfo(output_handle, &cursor_info)) {
		return;
	}


	width = buffer_info.srWindow.Right - buffer_info.srWindow.Left;
	height = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top;

	if (width * height > buffer_size)
	{
		buffer_size = width * height;
		// hopefully this will never fail.
		// what if we are making the screen smaller? 
		buffer = (CHAR_INFO * )realloc(buffer, sizeof(CHAR_INFO) * buffer_size);
	}

	return;
}

void Console::Print()
{
	UpdateScreenSize(); 
	COORD bufferSize = { width, height };
	COORD bufferCoord = { 0, 0 };
	SMALL_RECT writeRegion = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };


	WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);
	SetConsoleCursorPosition(hConsole, {0, 0});
}


void Console::PutChar(CHAR ch)
{
	if (ch == '\n')
	{
		while (cursor.X < width)
		{
			buffer[cursor.X + cursor.Y * width].Char.UnicodeChar = ' ';
			buffer[cursor.X + cursor.Y * width].Attributes = this->attributes;
			cursor.X++;
		}
		cursor.X = indent;
		cursor.Y++;
		return;
	}
	// Check if cursor is within bounds
	if (cursor.X < width && cursor.Y < height) {
		buffer[cursor.X + cursor.Y * width].Char.UnicodeChar= ch; // Write character
		buffer[cursor.X + cursor.Y * width].Attributes = this->attributes;

		// Move the cursor to the next position
		cursor.X++;
		if (cursor.X >= width) {
			cursor.X = indent;
			cursor.Y++;
		}
		if (cursor.Y >= height) {
			cursor.Y = height - 1; // Prevent cursor overflow
		}
	}
	
}



void Console::PutChars(CHAR* ch, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		PutChar(ch[i]);
	}
}

void Console::PutChars(const CHAR* ch, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		PutChar(ch[i]);
	}
}

void Console::PutString(std::string s)
{
	// a  bit shit
	CHAR* ch = new CHAR[s.size()+1];
	strcpy_s(ch, sizeof(CHAR) * (s.size() +1), s.c_str());
	PutChars(ch, s.size());
	delete ch;
}

void Console::PutStringLn(std::string s)
{
	PutString(s);
	PutChar('\n');
}

void Console::SetCursorPosition(SHORT x, SHORT y)
{
	cursor.X = (0 <= x && x <= width) ? x : cursor.X;
	cursor.Y = (0 <= y && y <= height) ? y : cursor.Y;
}

void Console::Clear()
{
	UpdateScreenSize();
	for (size_t i = 0; i < width * height; i++)
	{
		this->buffer[i].Char.UnicodeChar = ' ';
		this->buffer[i].Attributes = this->attributes;
	}

	cursor = { indent, 0 };
}

void Console::SetTitle(LPCSTR title)
{
	SetConsoleTitleA(title);
}

void Console::SetAttribute(WORD attribute)
{
	attributes = attribute;
}

void Console::SetIndent(SHORT i)
{
	indent = i;
}