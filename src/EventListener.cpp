#include "./EventListener.h"

void EventListener::MainLoop()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) 
		{
			std::cout << "Down key is pressed.\n";
			continue;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) 
		{
			std::cout << "Up key is pressed\n";
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000) 
		{
			std::cout << "Enter key is pressed\n";
			continue;
		}


		Sleep(75);
	}

}