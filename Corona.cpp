// Corona.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "Engine.h"
#include <Windows.h>

int __stdcall wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    Engine engine;

    // Game Loop
    while (engine.getWindowIsOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            engine.reset();
        }

        engine.updateDt();

        engine.update();

        engine.render();
    }

    return 0;
}
