#include "Game.h"
#include <vector>
#include <iostream>
#include "Window.h"
#include <cassert>

Game::Game()
	: Game(1280, 720)
{
}

Game::Game(uint32_t width, uint32_t height)
{
	m_window = Window(width, height, "Sea Battle");
	m_window.SetClearColor(sf::Color::Black);

	assert(m_window.FontFromFile("ofont.ru_Hero.ttf") || "Error opening font file");

	// set starting scene
	m_Scene = Scene::SETUP;
}

Game::~Game()
{
}

void Game::Play()
{
	// game loop
	while(m_Playing)
	{	
		// update keyboard and mouse state
		// check if the window was closed
		m_window.PollEvents();
		if (!m_window.IsOpen())
			break;

		// clear OpenGL buffer
		m_window.Clear();

		// Choose game scene
		switch (m_Scene)
		{
		case Game::Scene::SETUP:
			if (!PlaceShipsScene())
				m_Scene = Scene::SHOOTING;
			break;

		case Game::Scene::SHOOTING:
			if (!BattleScene())
				m_Scene = Scene::CHANGING_PLAYER;
			break;

		case Game::Scene::CHANGING_PLAYER:
			if (!ChangingPlayerScene())
				m_Scene = Scene::GAME_OVER;
			break;

		case Game::Scene::GAME_OVER:
			if (!GameOverScene())
				m_Scene = Scene::SETUP;
			break;

		default: break;
		}

		// draw scene
		m_window.Display();
	}

}

bool Game::PlaceShipsScene()
{
	// read mouse position
	int mouseX, mouseY;
	m_window.GetMousePos(mouseX, mouseY);

	// choose ship size
	if (m_window.GetKeyState(sf::Keyboard::Key::Num1) == Keystate::PRESSED)
	{

	}else if (m_window.GetKeyState(sf::Keyboard::Key::Num2) == Keystate::PRESSED)
	{

	}else if (m_window.GetKeyState(sf::Keyboard::Key::Num3) == Keystate::PRESSED)
	{

	}else if (m_window.GetKeyState(sf::Keyboard::Key::Num4) == Keystate::PRESSED)
	{

	}



	// place ship
	if (m_window.GetKeyState(sf::Mouse::Button::Right) == Keystate::PRESSED)
	{
	}




	return true;
}

bool Game::BattleScene()
{
	// делать ходы
	return false;
}

bool Game::ChangingPlayerScene()
{
	// скрыть поля пока игроки меняются местами
	return false;
}

bool Game::GameOverScene()
{
	// начать игру заново или выйти из игры
	return false;
}

void Game::SetPlayerAction(Player player, PlayerAction* action)
{
	switch (player)
	{
	case Game::Player::ONE:
		m_Player1 = std::unique_ptr<PlayerAction>(action);
		break;
	case Game::Player::TWO:
		m_Player2 = std::unique_ptr<PlayerAction>(action);
		break;
	default:
		break;
	}
}

bool Game::LoadFromFile(const char* filepath_1, const char* filepath_2)
{
	bool res1 = Player_1_invisible.LoadFromFile(filepath_1);
	bool res2 = Player_2_invisible.LoadFromFile(filepath_2);

	return res1 && res2;
}

bool Game::CheckForDeadShip(unsigned int x, unsigned int y, Field& visible, Field& invisible)
{
	Coords DirectionsOfCheck[4]{ {1,0}, {-1,0}, {0,1}, {0,-1} };
	Coords Sides[4]{ {0,1}, {0,1}, {1,0}, {1,0} };
	std::vector<Coords> CoordsOfMisses;

	for (int i = 0; i < 4; i++)
	{
		Field::State cell = Field::State::EMPTY;
		Coords tmp = { x, y };
		do
		{
			tmp = { tmp.x + DirectionsOfCheck[i].x, tmp.y + DirectionsOfCheck[i].y };
			cell = invisible.GetState(tmp.x, tmp.y);

			if (cell == Field::State::SHIP && visible.GetState(tmp.x, tmp.y) == Field::State::EMPTY) // Если в корабль не попали или он не убит возвращает false
				return false;

			// Запись координат всех клеток поля, вокруг корабля, где необходимо установить значения MISS если корабль убит
			CoordsOfMisses.push_back({ tmp.x + Sides[i].x, tmp.y + Sides[i].y });
			CoordsOfMisses.push_back({ tmp.x - Sides[i].x, tmp.y - Sides[i].y });

		} while (cell != Field::State::EMPTY && cell != Field::State::MISS);

		CoordsOfMisses.push_back(tmp);
	}

	for (Coords miss : CoordsOfMisses)
	{
		visible.SetState(Field::State::MISS, miss.x, miss.y);
		invisible.SetState(Field::State::MISS, miss.x, miss.y);
	}
	return true;
}

// FIX THIS SHIT
/*
bool Game::HIT(unsigned int x, unsigned int y, Field& visible, Field& invisible)
{
	if (invisible.GetState(x, y) == Field::State::EMPTY)
	{
		visible.SetState(Field::State::MISS, x, y);
		invisible.SetState(Field::State::MISS, x, y);
		return false;
	}
	else if (invisible.GetState(x, y) == Field::State::SHIP)
	{
		visible.SetState(Field::State::HIT, x, y);
		invisible.SetState(Field::State::HIT, x, y);
		return true;
	}
}


void Game::PlayerVersusPlayer()
{
	unsigned int NumberOfHits_1 = 0;
	unsigned int NumberOfHits_2 = 0;
	bool Player_1_win = 1; bool Player_2_win = 1;
	unsigned int x = 0;	unsigned int y = 0;

	bool Who_turn = 1;
	m_window.Clear();
	m_window.PrintField(Who_turn, Player_1_invisible); // Вывод пустых полей

	m_window.PlacementOfShips(Who_turn, x, y, Player_1_invisible); // Игрок 1 расставляет корабли
	m_window.Clear();
	Who_turn = !Who_turn;

	m_window.PrintField(Who_turn, Player_1_invisible); // Вывод пустых полей
	m_window.PlacementOfShips(Who_turn, x, y, Player_2_invisible); // Игрок 2 расставляет корабли
	Who_turn = !Who_turn;


	//while (Player_1_win && Player_2_win) // Цикл игры пока кто-то не проиграет
	//{
	////	std::cout << "\033[2J";
	//	m_window.Clear();
	//	m_window.PrintField(Who_turn, Player_1_visible, Player_2_visible); // Вывод полей по которым стреляют полей

	//	if (Who_turn == 1) // Если ходит игрок 1
	//	{
	//		sf::Event event;
	//		while (window.pollEvent(event))
	//		{
	//			if (event.type == sf::Event::Closed)
	//				window.close();
	//			if (event.type == sf::Event::MouseButtonPressed)
	//			{
	//				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	//				if (localPosition.x >= 530 && localPosition.x <= 848 && localPosition.y >= 82 && localPosition.y <= 400)
	//				{
	//					x = (localPosition.x - 530) / (30 + 2);
	//					y = (localPosition.y - 82) / (30 + 2);
	//					if (Player_1_visible.GetState(x, y) == 0)
	//					{
	//						if (!HIT(x, y, Player_2_visible, Player_2_invisible))
	//						{
	//							Who_turn = 0;
	//						}
	//						else
	//						{
	//							CheckForDeadShip(x, y, Player_2_visible, Player_2_invisible);
	//							NumberOfHits_1++;
	//						}
	//					}
	//					else
	//					{
	//						std::cout << "BRUH" << std::endl;
	//					}
	//				}
	//				else
	//				{
	//					std::cout << "BRUH" << std::endl;
	//				}
	//			}
	//		}
	//	}
	//	else if (Who_turn == 0) // Если ходит игрок 2
	//	{
	//		sf::Event event;
	//		while (window.pollEvent(event))
	//		{
	//			if (event.type == sf::Event::Closed)
	//				window.close();
	//			if (event.type == sf::Event::MouseButtonPressed)
	//			{
	//				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	//				if (localPosition.x >= 82 && localPosition.x <= 400 && localPosition.y >= 82 && localPosition.y <= 400)
	//				{
	//					x = (localPosition.x - 82) / (30 + 2);
	//					y = (localPosition.y - 82) / (30 + 2);
	//					if (Player_1_visible.GetState(x, y) == 0)
	//					{
	//						if (!HIT(x, y, Player_1_visible, Player_1_invisible))
	//						{
	//							Who_turn = 1;
	//						}
	//						else
	//						{
	//							CheckForDeadShip(x, y, Player_1_visible, Player_1_invisible);
	//							NumberOfHits_2++;
	//						}
	//					}
	//					else
	//					{
	//						std::cout << "BRUH" << std::endl;
	//					}
	//				}
	//				else
	//				{
	//					std::cout << "BRUH" << std::endl;
	//				}
	//			}
	//		}
	//	}
	//	if (NumberOfHits_1 == 20)
	//	{
	//		Player_2_win = 0;
	//	}
	//	else if (NumberOfHits_2 == 20)
	//	{
	//		Player_1_win = 0;
	//	}
	//}
	//if (Player_1_win)
	//{
	//	std::cout << "Игрок 1 победил!";
	//}
	//else if (Player_2_win)
	//{
	//	std::cout << "Игрок 2 победил!";
	//}
	//window.clear();
	//Window::PrintField(window, Who_turn, Player_2_visible, Player_1_visible);
	//window.display();
}
*/

