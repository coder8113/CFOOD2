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

		if (GetAsyncKeyState(VK_BACK) & 0x8000)
		{
			callback(VK_BACK);
		}
		
		int VK_A = 0x41;
		int VK_Z = 0x5A;
		for (int vk_letter = 0x41; vk_letter <= VK_Z; vk_letter++)
		{
			if (GetAsyncKeyState(vk_letter) & 0x8000)
			{
				callback(vk_letter);
			}
		}


		Sleep(60);
	}

}

std::function<void(int)> EventListener::callback;