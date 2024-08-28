#pragma once

#include <windows.h>
#include <iostream>
#include <functional>

class EventListener
{
public:
	void static MainLoop();

	static std::function<void(int)> callback;
	void static setCallback(const std::function<void(int)>& cb) { callback = cb; }



};

