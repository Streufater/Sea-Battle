#pragma once
#include "Field.h"
#include "Window.h"
#include "PlayerAction.h"
#include <memory>

class Game
{
public:
	enum class Scene
	{
		SETUP,
		SHOOTING,
		CHANGING_PLAYER,
		GAME_OVER,
	};

	enum class PlayerType
	{
		AI,
		HUMAN
	};

	enum class Player
	{
		ONE,
		TWO
	};

	// Initialize game
	Game();
	Game(uint32_t width, uint32_t height);
	~Game();
	void SetPlayerAction(Player player, PlayerAction* action);
	bool LoadFromFile(const char* filepath_1, const char* filepath_2);

	// main loop
	void Play();

private:
	// scene functions. return false if scene ended. return true if scene running
	bool PlaceShipsScene();
	bool BattleScene();
	bool ChangingPlayerScene();
	bool GameOverScene();

	// helper functions
	bool CheckForDeadShip(unsigned int x, unsigned int y, Field& visible, Field& invisible);

	// delete
	//void PlayerVersusPlayer();
	//bool HIT(unsigned int x, unsigned int y, Field& visible, Field& invisible);

private:
	// game state
	bool m_Playing = true;
	Scene m_Scene;

	// Player data
	Field Player_1_visible;
	Field Player_1_invisible;

	Field Player_2_visible;
	Field Player_2_invisible;

	std::unique_ptr<PlayerAction> m_Player1;
	std::unique_ptr<PlayerAction> m_Player2;

	// window
	Window m_window;
};
