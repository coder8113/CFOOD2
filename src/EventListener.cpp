#include "./EventListener.h"

void EventListener::MainLoop()
{
	while (true)
	{
		if (GetAsyncKeyState('W') & 0x8000) 
		{
			std::cout << "'W' key is pressed.\n";
		}

		Sleep(75);
	}

}