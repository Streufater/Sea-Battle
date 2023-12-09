#pragma once
#include "Field.h"
#include "Window.h"

class Game
{
public:

	Game();
	~Game();

	bool LoadFromFile(const char* filepath_1, const char* filepath_2);

	void PrintMurkup();
	void PrintEmptyField();
	void PrintField(bool Who_turn, Field& invisible);
	void PrintField(bool Who_turn, Field& Player_1_field, Field& Player_2_field);
	void PlacementOfShips(bool Who_turn, unsigned int x, unsigned int y, Field& invisible);

	bool HIT(unsigned int x, unsigned int y, Field& visible, Field& invisible);
	bool CheckForDeadShip(unsigned int x, unsigned int y, Field& visible, Field& invisible);
	bool CheckForCorrectShipPosition(unsigned int x, unsigned int y, Field invisible, bool isVertical, int SelectedShipSize);

	void PlayerVersusPlayer();

private:

	Field Player_1_visible;
	Field Player_1_invisible;

	Field Player_2_visible;
	Field Player_2_invisible;

	Window m_window;
};

