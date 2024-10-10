#include "./Console.h"

HANDLE Console::hConsole = nullptr;  
CONSOLE_SCREEN_BUFFER_INFO Console::buffer_info; 
size_t Console::buffer_size = 0; 
CHAR_INFO* Console::buffer = nullptr; 
COORD Console::cursor = { 0, 0 }; 
WORD Console::attributes = 0;
SHORT Console::width = 0; 
SHORT Console::height = 0; 
SHORT Console::indent = 0; 

void Console::Init()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	UpdateScreenSize();
	buffer_size = width * height;
	buffer = (CHAR_INFO *)malloc(sizeof(CHAR_INFO) * width*height);
	cursor = { 0, 0 };
	indent = 0;
	attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	Clear();
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
	height = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;

	if (width * height > buffer_size)
	{
		buffer_size = (width) * (height);
		// hopefully this will never fail.
		// what if we are making the screen smaller? 
		system("cls");
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
	if (cursor.X >= width - 1 && cursor.Y >= height - 1)
	{
		return;
	}

	if (ch == '\n')
	{
		while (cursor.X < width)
		{
			buffer[cursor.X + cursor.Y * width].Char.UnicodeChar = ' ';
			buffer[cursor.X + cursor.Y * width].Attributes = attributes;
			cursor.X++;
		}
		cursor.X = indent;
		cursor.Y++;
		return;
	}
	// Check if cursor is within bounds
	if (cursor.X < width && cursor.Y < height) {
		buffer[cursor.X + cursor.Y * width].Char.UnicodeChar= ch; // Write character
		buffer[cursor.X + cursor.Y * width].Attributes = attributes;

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
	//delete ch;
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
	for (size_t i = 0; i < buffer_size; i++)
	{
		buffer[i].Char.UnicodeChar = ' ';
		buffer[i].Attributes = attributes;

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

void Console::unittest() {
	// Test toLowerCase function
	std::cout << "Console Tests." << std::endl;
	height = 100;
	width = 100;
	assert(getHeight() == 100);
	assert(getWidth() == 100);
	
	buffer_size = width * height;
	buffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * width * height);
	cursor = { 0, 0 };
	indent = 0;
	attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	SetAttribute(FOREGROUND_BLUE);
	assert(attributes == FOREGROUND_BLUE);

	SetIndent(0);
	assert(indent == 0);
	assert(cursor.X == 0);
	assert(cursor.Y == 0);

	PutChar('a');
	assert(buffer[0].Char.UnicodeChar == 'a');
	assert(buffer[0].Attributes == FOREGROUND_BLUE);

	cursor.X = 0;
	cursor.Y = 0;

	char test1[5] = "char";
	PutChars(test1, 4);
	assert(buffer[0].Char.UnicodeChar == 'c');

	cursor.X = 0;
	cursor.Y = 0;

	const char test2[6] = "const";
	PutChars(test2, 5);
	assert(buffer[0].Char.UnicodeChar == 'c');

	cursor.X = 0;
	cursor.Y = 0;
	PutString("test");
	assert(buffer[0].Char.UnicodeChar == 't');

	cursor.X = 0;
	cursor.Y = 0;

	PutStringLn("test");
	assert(buffer[0].Char.UnicodeChar == 't');
	assert(buffer[4].Char.UnicodeChar == ' ');

	
	Clear();
	assert(buffer[0].Char.UnicodeChar == ' ');
}