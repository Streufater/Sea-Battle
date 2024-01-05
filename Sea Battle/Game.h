#pragma once
#include "Field.h"
#include "Window.h"
#include "BotAction.h"

class Game
{
public:

	enum class Player
	{
		Human,
		Bot,
	};

	Game();
	~Game();

	bool LoadFromFile(const char* filepath_1, const char* filepath_2);
	bool LoadToFile(const char* filepath_1, const char* filepath_2);

	void PrintMurkup();
	void PrintFieldBorders(bool Whose_turn);
	void PrintGuid();

	void PrintEmptyField();
	void PrintField(bool Who_turn, Field& invisible);
	void PrintField(bool Who_turn, Field& Player_1_field, Field& Player_2_field);

	void PrintSelectedShip(bool isVertical, int SelectedShipSize);
	void PlacementOfShips(bool Who_turn, unsigned int x, unsigned int y, Field& invisible);

	bool HIT(unsigned int x, unsigned int y, Field& visible, Field& invisible);
	bool CheckForDeadShip(unsigned int x, unsigned int y, Field& visible, Field& invisible);
	bool CheckForCorrectShipPosition(unsigned int x, unsigned int y, Field invisible, bool isVertical, int SelectedShipSize);

	void Play();

	void MainMenu();

	void MyBotActions(unsigned int& x, unsigned int& y, bool& Whose_turn, unsigned int& NumberOfHits_1);
	void EnemyBotActions(unsigned int& x, unsigned int& y, bool& Whose_turn, unsigned int& NumberOfHits_2);

private:

	BotAction* m_MyBot = nullptr;
	BotAction* m_EnemyBot = nullptr;

	Player first;
	Player second;

	Field Player_1_visible;
	Field Player_1_invisible;

	Field Player_2_visible;
	Field Player_2_invisible;

	Window m_window;
};

