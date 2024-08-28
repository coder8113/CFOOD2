#include "./EventListener.h"

void EventListener::MainLoop()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) 
		{
			callback(VK_DOWN);
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) 
		{
			callback(VK_UP);
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000) 
		{
			callback(VK_RETURN);
		}


		Sleep(120);
	}

}

std::function<void(int)> EventListener::callback;