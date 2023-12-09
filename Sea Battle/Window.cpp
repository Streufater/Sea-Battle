#include "Window.h"
#include <iostream>

Window::Window()
{
}

Window::~Window()
{
}

void Window::PrintField(sf::RenderWindow& window, bool Who_turn, Field& invisible)
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
        window.draw(text);
        text.setPosition(62, 76 + j);
        window.draw(text);
        text.setPosition(530 + j, 57);
        window.draw(text);
        text.setPosition(510, 76 + j);
        window.draw(text);
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
                case Field::EMPTY: square.setFillColor(sf::Color::Blue); break;
                case Field::SHIP: square.setFillColor(sf::Color::Yellow); break;
                case Field::MISS: square.setFillColor(sf::Color::Cyan); break;
                case Field::HIT: square.setFillColor(sf::Color::Red); break;
                default:break;
                }
                square.setPosition(b, k);
                window.draw(square);
            }

        for (int k = 82; k <= 400; k += 32)
            for (int b = 530; b <= 848; b += 32)
            {
                square.setFillColor(sf::Color::Blue);
                square.setPosition(b, k);
                window.draw(square);
            }
    }
    else if (Who_turn == 0)
    {
        for (int k = 82; k <= 400; k += 32)
            for (int b = 530; b <= 848; b += 32)
            {
                int x = (b - 530) / 32;
                int y = (k - 82) / 32;
                switch (invisible.GetState(x, y))
                {
                case Field::EMPTY: square.setFillColor(sf::Color::Blue); break;
                case Field::SHIP: square.setFillColor(sf::Color::Yellow); break;
                case Field::MISS: square.setFillColor(sf::Color::Cyan); break;
                case Field::HIT: square.setFillColor(sf::Color::Red); break;
                default:break;
                }
                    square.setPosition(b, k);
                    window.draw(square);
            }
        for (int k = 82; k <= 400; k += 32)
            for (int b = 82; b <= 400; b += 32)
            {
                square.setFillColor(sf::Color::Blue);
                square.setPosition(b, k);
                window.draw(square);
            }
    }
}

void Window::PrintField(sf::RenderWindow& window, bool Who_turn, Field& Player_1_field, Field& Player_2_field)
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
        window.draw(text);
        text.setPosition(62, 76 + j);
        window.draw(text);
        text.setPosition(530 + j, 57);
        window.draw(text);
        text.setPosition(510, 76 + j);
        window.draw(text);
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
                case Field::EMPTY: square.setFillColor(sf::Color::Blue); break;
                case Field::SHIP: square.setFillColor(sf::Color::Yellow); break;
                case Field::MISS: square.setFillColor(sf::Color::Cyan); break;
                case Field::HIT: square.setFillColor(sf::Color::Red); break;
                default:break;
                }
                square.setPosition(b, k);
                window.draw(square);
            }

        for (int k = 82; k <= 400; k += 32)
            for (int b = 530; b <= 848; b += 32)
            {
                int x = (b - 530) / 32;
                int y = (k - 82) / 32;
                switch (Player_2_field.GetState(x, y))
                {
                case Field::EMPTY: square.setFillColor(sf::Color::Blue); break;
                case Field::SHIP: square.setFillColor(sf::Color::Yellow); break;
                case Field::MISS: square.setFillColor(sf::Color::Cyan); break;
                case Field::HIT: square.setFillColor(sf::Color::Red); break;
                default:break;
                }
                square.setPosition(b, k);
                window.draw(square);
            }
}

void Window::PlacementOfShips(sf::RenderWindow& window, bool Who_turn, unsigned int x, unsigned int y, Field& invisible)
{
    int SelectedShipSize = 0;
    bool isVertical = false;
    int CELL_SIZE = 30;
    int NumberOfSingleDeck = 0; int NumberOfDoubleDeck = 0;
    int NumberOfThreeDeck = 0; int NumberOfFourDeck = 0;


    while ((NumberOfSingleDeck + NumberOfDoubleDeck + NumberOfThreeDeck + NumberOfFourDeck) != 10)
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            window.clear();
            Window::PrintField(window, Who_turn, invisible);

            if (event.type == sf::Event::Closed)
                window.close();

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
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
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
                        invisible.Field::SetState(Field::SHIP, x, y + i);
                        window.clear();
                        Window::PrintField(window, Who_turn, invisible);
                    }
                }
                else if (!isVertical) {
                    for (int i = 0; i < SelectedShipSize; i++)
                    {
                        invisible.Field::SetState(Field::SHIP, x + i, y);
                        window.clear();
                        Window::PrintField(window, Who_turn, invisible);
                    }
                }
                window.display();
                SelectedShipSize = 0;
            }
        }
    }
}





















