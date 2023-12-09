#pragma once
#include "Field.h"

class Game
{
public:

	Game();
	~Game();

	bool LoadFromFile(const char* filepath_1, const char* filepath_2);

	void PlayerVersusPlayer();

	bool HIT(unsigned int x, unsigned int y, Field& visible, Field& invisible);

	bool CheckForDeadShip(unsigned int x, unsigned int y, Field& visible, Field& invisible);

private:

	Field Player_1_visible;
	Field Player_1_invisible;

	Field Player_2_visible;
	Field Player_2_invisible;


};

