#include "Window.h"
#include <iostream>

Window::Window()
{
}

Window::Window(unsigned int width, unsigned int height, const char* title)
{
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
    m_window->setVerticalSyncEnabled(true);
}

Window::~Window()
{
}

bool Window::FontFromFile(const char* filepath)
{
    return m_font.loadFromFile(filepath);
}

void Window::Clear()
{
    m_window->clear(m_clearColor);
}

void Window::SetClearColor(sf::Color color)
{
    m_clearColor = color;
}

bool Window::IsOpen()
{
    return m_window->isOpen();
}

void Window::Display()
{
    m_window->display();
}

void Window::GetMousePos(int& x, int& y)
{
    x = m_mouseX;
    y = m_mouseY;
}

Keystate Window::GetKeyState(sf::Keyboard::Key k)
{
    auto iter = m_keymap.find(k);
    // new key
    if (iter == m_keymap.end())
    {
        m_keymap[k] = Keystate::RELEASED;
        return Keystate::RELEASED;
    }

    return iter->second;
}

Keystate Window::GetKeyState(sf::Mouse::Button b)
{
    auto iter = m_mousemap.find(b);
    // new button
    if (iter == m_mousemap.end())
    {
        m_mousemap[b] = Keystate::RELEASED;
        return Keystate::RELEASED;
    }

    return iter->second;
}

void Window::PollEvents()
{
    // очищает предыдущий статус
    for (auto& pair : m_keymap)
        pair.second = Keystate::RELEASED;
    for (auto& pair : m_mousemap)
        pair.second = Keystate::RELEASED;

    // обновляет позицию мышки
    sf::Vector2i localPosition = sf::Mouse::getPosition(*m_window);
    m_mouseX = localPosition.x;
    m_mouseY = localPosition.y;

    // обновляет ключевые состояния
    sf::Event event;
    while (m_window->pollEvent(event))
    {   // проверяет тип события
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::KeyPressed:
            m_keymap[event.key.code] = Keystate::PRESSED;
            break;
        case sf::Event::MouseButtonPressed:
            m_mousemap[event.mouseButton.button] = Keystate::PRESSED;
            break;
        default:
            break;
        }
    }
}

void Window::DrawRect(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color)
{
    m_square.setSize(size);
    m_square.setPosition(pos);
    m_square.setFillColor(color);
    m_window->draw(m_square);
}

void Window::DrawText(char& text, const sf::Vector2f& pos, const sf::Color& color, unsigned int size)
{
    sf::Text t;
    t.setFont(m_font);
    t.setCharacterSize(size);
    t.setFillColor(color);
    t.setPosition(pos);
    t.setString(text);
    m_window->draw(t);
}
























