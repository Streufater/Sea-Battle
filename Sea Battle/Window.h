#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"

#include <memory>
#include <map>

enum class Keystate
{
	PRESSED,
	RELEASED
};

class Window
{
public:
	// Setup
	Window();
	Window(uint32_t width, uint32_t height, const char* title);
	~Window();
	bool FontFromFile(const char* filepath);
	void SetClearColor(sf::Color color);

	// update
	void Clear();
	bool IsOpen();
	void Display();
	void PollEvents();

	// input
	void GetMousePos(int& x, int&y);
	Keystate GetKeyState(sf::Keyboard::Key k);
	Keystate GetKeyState(sf::Mouse::Button b);
	
	// draw
	void DrawRect(const sf::Vector2f& Size, const sf::Vector2f& pos, const sf::Color& color);
	void DrawText(const char* text, const sf::Vector2f& pos, const sf::Color& color, uint32_t size);

	// delete
	//void PrintField(bool Who_turn, Field& field);
	//void PrintField(bool Who_turn, Field& invisible, Field& visible);
	//void PlacementOfShips(bool Who_turn, unsigned int x, unsigned int y, Field& invisible);

private:
	// mouse and keyboard state
	std::map<sf::Keyboard::Key, Keystate> m_keymap;
	std::map<sf::Mouse::Button, Keystate> m_mousemap;
	int m_mouseX;
	int m_mouseY;

	// sfml window smart pointer
	std::shared_ptr<sf::RenderWindow> m_window;
	
	// window parameters
	sf::Color m_clearColor;
	sf::Font m_font;

	// square?
	sf::RectangleShape m_square;
};
