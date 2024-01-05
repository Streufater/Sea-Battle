#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include <memory>
#include <map>
#include <string>

enum class Keystate
{
	PRESSED,
	RELEASED
};

class Window
{

public:

	Window();
	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	bool FontFromFile(const char* filepath);
	void SetClearColor(sf::Color color);

	void Clear();
	bool IsOpen();
	void Display();

	void PollEvents();

	void GetMousePos(int& x, int& y);
	Keystate GetKeyState(sf::Keyboard::Key k);
	Keystate GetKeyState(sf::Mouse::Button b);

	void DrawRect(const sf::Vector2f& Size, const sf::Vector2f& pos, const sf::Color& color);
	void DrawTriangle(const sf::Vector2f& pos1, const sf::Vector2f& pos2, const sf::Vector2f& pos3, const sf::Color& color);
	void DrawText(char text, const sf::Vector2f& pos, const sf::Color& color, unsigned int size);
	void DrawString(std::wstring text, const sf::Vector2f pos, const sf::Color& color, unsigned int size);

private:

	std::map<sf::Keyboard::Key, Keystate> m_keymap;
	std::map<sf::Mouse::Button, Keystate> m_mousemap;
	int m_mouseX;
	int m_mouseY;

	std::shared_ptr<sf::RenderWindow> m_window;
	
	sf::RectangleShape m_square;
	sf::ConvexShape m_triangle;
	sf::Font m_font;
	sf::Color m_clearColor;
};

