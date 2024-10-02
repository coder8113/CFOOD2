#include "./EventListener.h"

void EventListener::MainLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK EventListener::CaptureKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

		if (GetForegroundWindow() == GetConsoleWindow()) {


			if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
				// if key press, pass the vkcall on
				callback(pKeyboard->vkCode);

				// Exit program
				if (pKeyboard->vkCode == VK_ESCAPE) {
					PostQuitMessage(0);
				}
			}
		}
	}
	
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}



std::function<void(int)> EventListener::callback;