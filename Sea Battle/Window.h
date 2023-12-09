#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"

class Window
{

public:

	
	Window();
	~Window();

	static void PrintField(sf::RenderWindow& window, bool Who_turn, Field& field);
	static void PrintField(sf::RenderWindow& window, bool Who_turn, Field& invisible, Field& visible);

	static void PlacementOfShips(sf::RenderWindow& window, bool Who_turn, unsigned int x, unsigned int y, Field& invisible);

	
private:


};

