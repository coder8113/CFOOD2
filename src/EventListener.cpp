#include "./EventListener.h"

void EventListener::MainLoop()
{
    MSG msg;
    DWORD lastTime = static_cast<DWORD>(GetTickCount64());  
    const DWORD interval = 150;  

    while (true) {

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return; 
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Check the time difference to call the callback every 150 ms
        DWORD currentTime = static_cast<DWORD>(GetTickCount64());
        if (currentTime - lastTime >= interval) {
            callback(INVALIDATED_DISPLAY);  
            lastTime = currentTime;  
        }

        Sleep(10);
    }
}

LRESULT CALLBACK EventListener::CaptureKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

        if (GetForegroundWindow() == GetConsoleWindow()) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                // If key press, pass the vkCode on
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