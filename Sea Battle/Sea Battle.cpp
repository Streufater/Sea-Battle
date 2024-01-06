#include <iostream>
#include "Game.h"



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
