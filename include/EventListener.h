/**
 * @file EventListener.h
 * @brief This file defines the EventListener class which handles key presses
 */
#pragma once

#include <windows.h>
#include <iostream>
#include <functional>

/**
 * @brief The EventListener class handles event listening and provides functionality to set
 * a callback that will be triggered during the main loop.
 */
class EventListener
{
public:
    /**
     * @brief Starts the main event loop. This function handles dispatching windows messages.
     * and calls the registered callback when an event occurs.
     */
    static void MainLoop();

    /**
    * @brief Hook procedure to capture windows keypresses. This will pass
    * the pressed vk and run the callback routine.
    */
    static LRESULT CALLBACK CaptureKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);


    /**
     * @brief Sets the callback function that will be called when an event is detected.
     * 
     * @param cb A function that takes an integer as a parameter, representing the event.
     */
    static void setCallback(const std::function<void(int)>& cb) { callback = cb; }

    /**
     * @brief A function that will be called when an event is detected in the main loop.
     * The integer parameter typically represents the event type or code.
     */
    static std::function<void(int)> callback;
};
