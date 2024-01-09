#include <iostream>
#include "Game.h"

#if defined(NDEBUG)
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
    Game game;
    bool PlayAgain = true;
    while (PlayAgain)
    {
        game.MainMenu();
        PlayAgain = game.Play();
    }
    return 0;
}
