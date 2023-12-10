
#include <iostream>
#include "Field.h"
#include "Game.h"
#include "Window.h"
#include <SFML/Graphics.hpp>



int main()
{
    setlocale(LC_ALL, "Russian");

    Game game;
    //if (game.LoadFromFile("Pole_1.txt", "Pole_2.txt") == false)
    //    return -1;
    //game.PlayerVersusPlayer();
    game.Play();

    return 0;
}

