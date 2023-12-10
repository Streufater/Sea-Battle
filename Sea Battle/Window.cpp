#include "Window.h"
#include <iostream>

Window::Window()
{
}

Window::Window(uint32_t width, uint32_t height, const char* title)
{
    // —здание окна
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
    // swap OpenGL buffers
    m_window->display();
}

void Window::PollEvents()
{
    // clear previous states
    for (auto& pair : m_keymap)
        pair.second = Keystate::RELEASED;
    for (auto& pair : m_mousemap)
        pair.second = Keystate::RELEASED;

    // update mouse position
    sf::Vector2i localPosition = sf::Mouse::getPosition(*m_window);
    m_mouseX = localPosition.x;
    m_mouseY = localPosition.y;

    // update key states
    sf::Event event;
    while (m_window->pollEvent(event))
    {   // check the type of the event
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

void Window::DrawRect(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color)
{   
    m_square.setSize(size);
    m_square.setPosition(pos);
    m_square.setFillColor(color);
    m_window->draw(m_square);
}

void Window::DrawText(const char* text, const sf::Vector2f& pos, const sf::Color& color, uint32_t size)
{
    sf::Text t;
    t.setFont(m_font);
    t.setCharacterSize(size);
    t.setFillColor(color);
    t.setPosition(pos);
    t.setString(text);
    m_window->draw(t);
}

// delete
/*
void Window::PrintField(bool Who_turn, Field& invisible)
{
    sf::Text text;
    sf::Font font;

    font.loadFromFile("ofont.ru_Hero.ttf");
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    int j = 12;
    for (char i = '0'; i <= '9'; i++)
    {
        text.setString(i);
        text.setPosition(82 + j, 57);
        m_window->draw(text);
        text.setPosition(62, 76 + j);
        m_window->draw(text);
        text.setPosition(530 + j, 57);
        m_window->draw(text);
        text.setPosition(510, 76 + j);
        m_window->draw(text);
        j += 32;
    }

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(30, 30));
    
    if (Who_turn == 1)
    {
        for (int k = 82; k <= 400; k += 32)
            for (int b = 82; b <= 400; b += 32)
            {
                int x = (b - 82) / 32;
                int y = (k - 82) / 32;
                switch (invisible.GetState(x,y))
                {
                case Field::State::EMPTY: square.setFillColor(sf::Color::Blue); break;
                case Field::State::SHIP: square.setFillColor(sf::Color::Yellow); break;
                case Field::State::MISS: square.setFillColor(sf::Color::Cyan); break;
                case Field::State::HIT: square.setFillColor(sf::Color::Red); break;
                default:break;
                }
                square.setPosition(b, k);
                m_window->draw(square);
            }

        for (int k = 82; k <= 400; k += 32)
            for (int b = 530; b <= 848; b += 32)
            {
                square.setFillColor(sf::Color::Blue);
                square.setPosition(b, k);
                m_window->draw(square);
            }
    }
    else if (Who_turn == 0)
    {
        for (int k = 82; k <= 400; k += 32)
        {
            for (int b = 530; b <= 848; b += 32)
            {
                int x = (b - 530) / 32;
                int y = (k - 82) / 32;
                switch (invisible.GetState(x, y))
                {
                case Field::State::EMPTY: square.setFillColor(sf::Color::Blue); break;
                case Field::State::SHIP: square.setFillColor(sf::Color::Yellow); break;
                case Field::State::MISS: square.setFillColor(sf::Color::Cyan); break;
                case Field::State::HIT: square.setFillColor(sf::Color::Red); break;
                default:break;
                }
                    square.setPosition(b, k);
                    m_window->draw(square);
            }
        }

        for (int k = 82; k <= 400; k += 32)
        {
            for (int b = 82; b <= 400; b += 32)
            {
                square.setFillColor(sf::Color::Blue);
                square.setPosition(b, k);
                m_window->draw(square);
            }
        }
    }
    m_window->display();
}

void Window::PrintField( bool Who_turn, Field& Player_1_field, Field& Player_2_field)
{
    sf::Text text;
    sf::Font font;

    font.loadFromFile("ofont.ru_Hero.ttf");
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    int j = 12;
    for (char i = '0'; i <= '9'; i++)
    {
        text.setString(i);
        text.setPosition(82 + j, 57);
        m_window->draw(text);
        text.setPosition(62, 76 + j);
        m_window->draw(text);
        text.setPosition(530 + j, 57);
        m_window->draw(text);
        text.setPosition(510, 76 + j);
        m_window->draw(text);
        j += 32;
    }

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(30, 30));

        for (int k = 82; k <= 400; k += 32)
            for (int b = 82; b <= 400; b += 32)
            {
                int x = (b - 82) / 32;
                int y = (k - 82) / 32;
                switch (Player_1_field.GetState(x, y))
                {
                case Field::State::EMPTY: square.setFillColor(sf::Color::Blue); break;
                case Field::State::SHIP: square.setFillColor(sf::Color::Yellow); break;
                case Field::State::MISS: square.setFillColor(sf::Color::Cyan); break;
                case Field::State::HIT: square.setFillColor(sf::Color::Red); break;
                default:break;
                }
                square.setPosition(b, k);
                m_window->draw(square);
            }

        for (int k = 82; k <= 400; k += 32)
            for (int b = 530; b <= 848; b += 32)
            {
                int x = (b - 530) / 32;
                int y = (k - 82) / 32;
                switch (Player_2_field.GetState(x, y))
                {
                case Field::State::EMPTY: square.setFillColor(sf::Color::Blue); break;
                case Field::State::SHIP: square.setFillColor(sf::Color::Yellow); break;
                case Field::State::MISS: square.setFillColor(sf::Color::Cyan); break;
                case Field::State::HIT: square.setFillColor(sf::Color::Red); break;
                default:break;
                }
                square.setPosition(b, k);
                m_window->draw(square);
            }
}

void Window::PlacementOfShips(bool Who_turn, unsigned int x, unsigned int y, Field& invisible)
{
    int SelectedShipSize = 0;
    bool isVertical = false;
    int CELL_SIZE = 30;
    int NumberOfSingleDeck = 0; int NumberOfDoubleDeck = 0;
    int NumberOfThreeDeck = 0; int NumberOfFourDeck = 0;


    while ((NumberOfSingleDeck + NumberOfDoubleDeck + NumberOfThreeDeck + NumberOfFourDeck) != 10)
    {

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            Clear();
            PrintField(Who_turn, invisible);

            if (event.type == sf::Event::Closed)
                m_window->close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1 && NumberOfSingleDeck != 4)
                {
                    SelectedShipSize = 1;
                }
                else if (event.key.code == sf::Keyboard::Num2 && NumberOfDoubleDeck != 3)
                {
                    SelectedShipSize = 2;
                }
                else if (event.key.code == sf::Keyboard::Num3 && NumberOfThreeDeck != 2)
                {
                    SelectedShipSize = 3;
                }
                else if (event.key.code == sf::Keyboard::Num4 && NumberOfFourDeck != 1)
                {
                    SelectedShipSize = 4;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    isVertical = !isVertical;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*m_window.get());
                if (Who_turn == 1 && localPosition.x >= 82 && localPosition.x <= 400 && localPosition.y >= 82 && localPosition.y <= 400)
                {
                    x = (localPosition.x - 82) / (CELL_SIZE + 2);
                    y = (localPosition.y - 82) / (CELL_SIZE + 2);
                }
                else if (Who_turn == 0 && localPosition.x >= 530 && localPosition.x <= 848 && localPosition.y >= 82 && localPosition.y <= 400)
                {
                    x = (localPosition.x - 530) / (CELL_SIZE + 2);
                    y = (localPosition.y - 82) / (CELL_SIZE + 2);
                }

                if (SelectedShipSize == 4){
                    NumberOfFourDeck++;
                }
                else if (SelectedShipSize == 3){
                    NumberOfThreeDeck++;
                }
                else if (SelectedShipSize == 2){
                    NumberOfDoubleDeck++;
                }
                else if (SelectedShipSize == 1){
                    NumberOfSingleDeck++;
                }
                if (isVertical) {
                    for (int i = 0; i < SelectedShipSize; i++)
                    {
                        invisible.Field::SetState(Field::State::SHIP, x, y + i);
                        Clear();
                        PrintField(Who_turn, invisible);
                    }
                }
                else if (!isVertical) {
                    for (int i = 0; i < SelectedShipSize; i++)
                    {
                        invisible.Field::SetState(Field::State::SHIP, x + i, y);
                        Clear();
                        PrintField(Who_turn, invisible);
                    }
                }
                m_window->display();
                SelectedShipSize = 0;
            }
        }
    }
}
*/

