#include "Game.h"
#include "Window.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

Game::Game()
{
    m_window = Window(930, 700, "Sea Batlle");
    m_window.FontFromFile("ofont.ru_Ramona.ttf");

    // Init Bots
    m_MyBot = new FirstBotAction();
    m_EnemyBot = new SecondBotAction();
    m_MyBot->Init();
    m_EnemyBot->Init();
}

Game::~Game()
{
    delete(m_MyBot);
    delete(m_EnemyBot);
}

struct Coords
{
    unsigned int x;
    unsigned int y;
};

bool Game::LoadFromFile(const char* filepath_1, const char* filepath_2)
{
    bool res1 = Player_2_visible.Field::LoadFromFile(filepath_1);
    bool res2 = Player_2_invisible.Field::LoadFromFile(filepath_2);
    return res1 && res2;
}

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
    return false;
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

bool Game::CheckForCorrectShipPosition(unsigned int x, unsigned int y, Field invisible, bool isVertical, int SelectedShipSize)
{
    if (isVertical)
    {
        for (int i = -1; i <= SelectedShipSize; i++)
            for (int j = -1; j <= 1; j++)
                if (invisible.GetState(x + j, y + i) == Field::State::SHIP)
                    return false;

        for (int i = 0; i < SelectedShipSize; i++)
            if (y + i > 9)
                return false;
    }
    else if (!isVertical)
    {
        for (int i = -1; i <= SelectedShipSize; i++)
            for (int j = -1; j <= 1; j++)
                if (invisible.GetState(x + i, y + j) == Field::State::SHIP)
                    return false;

        for (int i = 0; i < SelectedShipSize; i++)
            if (x + i > 9)
                return false;
    }

    return true;
}

void Game::PrintMurkup()
{
    sf::Text text;
    int j = 12;
    for (wchar_t i = '1'; i <= '9'; i++)
    {
        text.setString(i);

        m_window.DrawText(i, sf::Vector2f(62, 76 + j), sf::Color::White, 16);
        m_window.DrawText(i, sf::Vector2f(510, 76 + j), sf::Color::White, 16);
        j += 32;
    }
    m_window.DrawString(L"10", sf::Vector2f(55, 375), sf::Color::White, 18);
    m_window.DrawString(L"10", sf::Vector2f(503, 375), sf::Color::White, 18);

    j = 12;
    for (wchar_t i = L'А'; i <= L'И'; i++)
    {
        text.setString(i);

        m_window.DrawText(i, sf::Vector2f(80 + j, 57), sf::Color::White, 16);
        m_window.DrawText(i, sf::Vector2f(528 + j, 57), sf::Color::White, 16);
        j += 32;
    }
    m_window.DrawText(L'К', sf::Vector2f(80 + 12 + 32 * 9, 57), sf::Color::White, 16);
    m_window.DrawText(L'К', sf::Vector2f(528 + 12 + 32 * 9, 57), sf::Color::White, 16);

    m_window.DrawString(L"Поле первого игрока:", sf::Vector2f(82, 30), sf::Color::White, 20);
    m_window.DrawString(L"Поле второго игрока:", sf::Vector2f(530, 30), sf::Color::White, 20);

}

void Game::PrintFieldBorders(bool Whose_turn)
{
    if (Whose_turn == 1)
    {
        m_window.DrawTriangle(sf::Vector2f(430, 142), sf::Vector2f(430, 340), sf::Vector2f(500, 241), sf::Color::Green);
        m_window.DrawRect(sf::Vector2f(5, 327), sf::Vector2f(525, 77), sf::Color::Green);
        m_window.DrawRect(sf::Vector2f(5, 327), sf::Vector2f(848, 77), sf::Color::Green);
        m_window.DrawRect(sf::Vector2f(327, 5), sf::Vector2f(525, 77), sf::Color::Green);
        m_window.DrawRect(sf::Vector2f(327, 5), sf::Vector2f(525, 400), sf::Color::Green);
    }
    else if (Whose_turn == 0)
    {
        m_window.DrawTriangle(sf::Vector2f(500, 142), sf::Vector2f(500, 340), sf::Vector2f(430, 241), sf::Color::Green);
        m_window.DrawRect(sf::Vector2f(5, 327), sf::Vector2f(77, 77), sf::Color::Green);
        m_window.DrawRect(sf::Vector2f(5, 327), sf::Vector2f(400, 77), sf::Color::Green);
        m_window.DrawRect(sf::Vector2f(327, 5), sf::Vector2f(77, 77), sf::Color::Green);
        m_window.DrawRect(sf::Vector2f(327, 5), sf::Vector2f(77, 400), sf::Color::Green);
    }
}

void Game::PrintGuid()
{
    m_window.DrawString(L"1, 2, 3, 4 - размер корабля", sf::Vector2f(20, 580), sf::Color::White, 16);
    m_window.DrawString(L"Space - поворот корабля на 90 градусов", sf::Vector2f(20, 615), sf::Color::White, 16);
    m_window.DrawString(L"Перед тем как поставить корабль выберете его размер!", sf::Vector2f(20, 650), sf::Color::White, 16);
}

void Game::PrintEmptyField()
{
    PrintMurkup();
    for (int k = 82; k <= 400; k += 32)
        for (int b = 82; b <= 400; b += 32)
        {
            m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Blue);
        }

    for (int k = 82; k <= 400; k += 32)
        for (int b = 530; b <= 848; b += 32)
        {
            m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Blue);
        }
}

//Для стадии расстановки кораблей
void Game::PrintField(bool Whose_turn, Field& invisible)
{
    PrintMurkup();
    PrintGuid();
    PrintFieldBorders(!Whose_turn);
    if (Whose_turn == 1)
    {
        for (int k = 82; k <= 400; k += 32)
            for (int b = 82; b <= 400; b += 32)
            {
                int x = (b - 82) / 32;
                int y = (k - 82) / 32;
                switch (invisible.GetState(x, y))
                {
                case Field::State::EMPTY: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Blue); break;
                case Field::State::SHIP: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Yellow); break;
                case Field::State::MISS: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Cyan); break;
                case Field::State::HIT: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Red); break;
                default:break;
                }
            }
        for (int k = 82; k <= 400; k += 32)
            for (int b = 530; b <= 848; b += 32)
            {
                m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Blue);
            }
    }
    else if (Whose_turn == 0)
    {
        for (int k = 82; k <= 400; k += 32)
            for (int b = 530; b <= 848; b += 32)
            {
                int x = (b - 530) / 32;
                int y = (k - 82) / 32;
                switch (invisible.GetState(x, y))
                {
                case Field::State::EMPTY: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Blue); break;
                case Field::State::SHIP: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Yellow); break;
                case Field::State::MISS: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Cyan); break;
                case Field::State::HIT: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Red); break;
                default:break;
                }
            }
        for (int k = 82; k <= 400; k += 32)
            for (int b = 82; b <= 400; b += 32)
            {
                m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Blue);
            }
    }
}

//Для основной стадии игры
void  Game::PrintField(bool Whose_turn, Field& Player_1_field, Field& Player_2_field)
{
    PrintMurkup();
    PrintFieldBorders(Whose_turn);
    for (int k = 82; k <= 400; k += 32)
    {
        for (int b = 82; b <= 400; b += 32)
        {
            int x = (b - 82) / 32;
            int y = (k - 82) / 32;
            switch (Player_1_field.GetState(x, y))
            {
            case Field::State::EMPTY: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Blue); break;
            case Field::State::MISS: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Cyan); break;
            case Field::State::HIT: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Red); break;
            case Field::State::SHIP: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Yellow); break;
            default:break;
            }
        }
    }

    for (int k = 82; k <= 400; k += 32)
    {
        for (int b = 530; b <= 848; b += 32)
        {
            int x = (b - 530) / 32;
            int y = (k - 82) / 32;
            switch (Player_2_field.GetState(x, y))
            {
            case Field::State::EMPTY: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Blue); break;
            case Field::State::MISS: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Cyan); break;
            case Field::State::HIT: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Red); break;
            case Field::State::SHIP: m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(b, k), sf::Color::Yellow); break;
            default:break;
            }
        }
    }
}

void Game::PrintSelectedShip(bool isVertical, int SelectedShipSize)
{
    if (isVertical)
    {
        for (int i = 0; i < SelectedShipSize; i++)
        {
            m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(82, 430 + 30 * i + 2 * i), sf::Color::Yellow);
        }
    }
    else if (!isVertical)
    {
        for (int i = 0; i < SelectedShipSize; i++)
        {
            m_window.DrawRect(sf::Vector2f(30, 30), sf::Vector2f(82 + 30 * i + 2 * i, 430), sf::Color::Yellow);
        }
    }
}

//Стадия расстановки кораблей
void  Game::PlacementOfShips(bool Whose_turn, unsigned int x, unsigned int y, Field& invisible)
{
    int SelectedShipSize = 0;
    bool isVertical = false;
    int CELL_SIZE = 30;
    int NumberOfSingleDeck = 0; int NumberOfDoubleDeck = 0;
    int NumberOfThreeDeck = 0; int NumberOfFourDeck = 0;

    while ((NumberOfSingleDeck + NumberOfDoubleDeck + NumberOfThreeDeck + NumberOfFourDeck) < 10)
    {
        m_window.PollEvents();

        // choose ship size
        if (m_window.GetKeyState(sf::Keyboard::Key::Num1) == Window::Keystate::PRESSED)
        {
            if (NumberOfSingleDeck != 4)
            {
                SelectedShipSize = 1;
            }
        }
        else if (m_window.GetKeyState(sf::Keyboard::Key::Num2) == Window::Keystate::PRESSED)
        {
            if (NumberOfDoubleDeck != 3)
            {
                SelectedShipSize = 2;
            }
        }
        else if (m_window.GetKeyState(sf::Keyboard::Key::Num3) == Window::Keystate::PRESSED)
        {
            if (NumberOfThreeDeck != 2)
            {
                SelectedShipSize = 3;
            }
        }
        else if (m_window.GetKeyState(sf::Keyboard::Key::Num4) == Window::Keystate::PRESSED)
        {
            if (NumberOfFourDeck != 1)
            {
                SelectedShipSize = 4;
            }
        }
        else if (m_window.GetKeyState(sf::Keyboard::Key::Space) == Window::Keystate::PRESSED)
        {
            isVertical = !isVertical;
        }

        m_window.Clear();
        PrintField(Whose_turn, invisible);
        PrintSelectedShip(isVertical, SelectedShipSize);
        m_window.Display();

        if (m_window.GetKeyState(sf::Mouse::Button::Left) == Window::Keystate::PRESSED)
        {
            int mouseX, mouseY;
            m_window.GetMousePos(mouseX, mouseY);
            if (Whose_turn == 1 && mouseX >= 82 && mouseX <= 400 && mouseY >= 82 && mouseY <= 400)
            {
                x = (mouseX - 82) / (CELL_SIZE + 2);
                y = (mouseY - 82) / (CELL_SIZE + 2);
            }
            else if (Whose_turn == 0 && mouseX >= 530 && mouseX <= 848 && mouseY >= 82 && mouseY <= 400)
            {
                x = (mouseX - 530) / (CELL_SIZE + 2);
                y = (mouseY - 82) / (CELL_SIZE + 2);
            }
            if (CheckForCorrectShipPosition(x, y, invisible, isVertical, SelectedShipSize))
            {
                if (SelectedShipSize == 4) {
                    NumberOfFourDeck++;
                }
                else if (SelectedShipSize == 3) {
                    NumberOfThreeDeck++;
                }
                else if (SelectedShipSize == 2) {
                    NumberOfDoubleDeck++;
                }
                else if (SelectedShipSize == 1) {
                    NumberOfSingleDeck++;
                }
                if (isVertical)
                {
                    for (int i = 0; i < SelectedShipSize; i++)
                    {
                        invisible.Field::SetState(Field::State::SHIP, x, y + i); // place ship
                    }
                }
                else if (!isVertical)
                {
                    for (int i = 0; i < SelectedShipSize; i++)
                    {
                        invisible.Field::SetState(Field::State::SHIP, x + i, y); // place ship
                    }
                }
                SelectedShipSize = 0;
            }
        }
    }
}

bool Game::Play()
{
    unsigned int NumberOfHits_1 = 0;
    unsigned int NumberOfHits_2 = 0;
    bool Player_1_win = 1; bool Player_2_win = 1;
    unsigned int x = 10;	unsigned int y = 10;
    bool Whose_turn = 1;
    ShotResult MyLastHit = ShotResult::MISS;
    ShotResult EnemyLastHit = ShotResult::MISS;

    m_MyBot->Init();
    m_EnemyBot->Init();

    PrintEmptyField(); // Вывод пустых полей
    m_window.Display();

    if (first == Player::Human)
        PlacementOfShips(Whose_turn, x, y, Player_1_invisible); // Игрок 1 расставляет корабли
    else Player_1_invisible.Field::LoadFromFile("Pole_1.txt");

    m_window.Clear();
    Whose_turn = !Whose_turn;

    PrintEmptyField(); // Вывод пустых полей
    if (second == Player::Human)
        PlacementOfShips(Whose_turn, x, y, Player_2_invisible); // Игрок 2 расставляет корабли
    else Player_2_invisible.Field::LoadFromFile("Pole_2.txt");

    Whose_turn = !Whose_turn;

    while (Player_1_win && Player_2_win) // Цикл игры пока кто-то не проиграет
    {
        m_window.Clear();
        PrintField(Whose_turn, Player_1_visible, Player_2_visible); // Вывод полей по которым стреляют игроки
        m_window.Display();

        m_window.PollEvents(); //Считывание ивентов

        if (Whose_turn == 1 && first == Player::Human) // Если ходит игрок 1 и это человек
        {
            if (m_window.GetKeyState(sf::Mouse::Button::Left) == Window::Keystate::PRESSED)
            {
                int mouseX, mouseY;
                m_window.GetMousePos(mouseX, mouseY);

                if (mouseX >= 530 && mouseX <= 848 && mouseY >= 82 && mouseY <= 400)
                {
                    x = (mouseX - 530) / (30 + 2);
                    y = (mouseY - 82) / (30 + 2);
                    if (Player_2_visible.GetState(x, y) == Field::State::EMPTY)
                    {
                        if (!HIT(x, y, Player_2_visible, Player_2_invisible))
                        {
                            Whose_turn = 0;
                        }
                        else
                        {
                            CheckForDeadShip(x, y, Player_2_visible, Player_2_invisible);
                            NumberOfHits_1++;
                        }
                    }
                }
            }
        }
        else if (Whose_turn == 1 && first == Player::Bot) // Если ходит игрок 1 и это бот
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            m_MyBot->MakeTurn(x, y, MyLastHit, Player_2_visible);

            if (!HIT(x, y, Player_2_visible, Player_2_invisible))
            {
                MyLastHit = ShotResult::MISS;
                Whose_turn = 0;
            }
            else
            {
                if (CheckForDeadShip(x, y, Player_2_visible, Player_2_invisible))
                {
                    MyLastHit = ShotResult::DEAD;
                }
                else
                {
                    MyLastHit = ShotResult::HIT;
                }
                NumberOfHits_1++;
            }
        }
        else if (Whose_turn == 0 && second == Player::Human) // Если ходит игрок 2  и это человек
        {
            if (m_window.GetKeyState(sf::Mouse::Button::Left) == Window::Keystate::PRESSED)
            {
                int mouseX, mouseY;
                m_window.GetMousePos(mouseX, mouseY);

                if (mouseX >= 82 && mouseX <= 400 && mouseY >= 82 && mouseY <= 400)
                {
                    x = (mouseX - 82) / (30 + 2);
                    y = (mouseY - 82) / (30 + 2);
                    if (Player_1_visible.GetState(x, y) == Field::State::EMPTY)
                    {
                        if (!HIT(x, y, Player_1_visible, Player_1_invisible))
                        {
                            Whose_turn = 1;
                        }
                        else
                        {
                            CheckForDeadShip(x, y, Player_1_visible, Player_1_invisible);
                            NumberOfHits_2++;
                        }
                    }
                }
            }
        }
        else if (Whose_turn == 0 && second == Player::Bot) // Если ходит игрок 2 и это бот
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            m_EnemyBot->MakeTurn(x, y, EnemyLastHit, Player_1_visible);

            if (!HIT(x, y, Player_1_visible, Player_1_invisible))
            {
                EnemyLastHit = ShotResult::MISS;
                Whose_turn = 1;
            }
            else
            {
                if (CheckForDeadShip(x, y, Player_1_visible, Player_1_invisible))
                {
                    EnemyLastHit = ShotResult::DEAD;
                }
                else
                {
                    EnemyLastHit = ShotResult::HIT;
                }
                NumberOfHits_2++;
            }
        }

        //Проверка убиты и все корабли у одного из игроков
        if (NumberOfHits_1 == 20)
        {
            Player_2_win = 0;
            m_window.Clear();
            m_window.DrawString(L"Первый игрок победил !", sf::Vector2f(343, 450), sf::Color::White, 20);
        }
        else if (NumberOfHits_2 == 20)
        {
            Player_1_win = 0;
            m_window.Clear();
            m_window.DrawString(L"Второй игрок победил !", sf::Vector2f(343, 450), sf::Color::White, 20);
        }
    }

    m_window.DrawString(L"Играть снова ?", sf::Vector2f(391, 500), sf::Color::White, 20);
    m_window.DrawRect(sf::Vector2f(51, 40), sf::Vector2f(402, 535), sf::Color::Cyan);
    m_window.DrawString(L"Да", sf::Vector2f(414, 540), sf::Color::White, 20);

    m_window.DrawRect(sf::Vector2f(51, 40), sf::Vector2f(471, 535), sf::Color::Cyan);
    m_window.DrawString(L"Нет", sf::Vector2f(479, 540), sf::Color::White, 20);
    PrintField(Whose_turn, Player_1_invisible, Player_2_invisible); // Вывод двух конечных полей
    m_window.Display();

    while (!sf::Event::Closed)
    {
        m_window.PollEvents();
        if (m_window.GetKeyState(sf::Mouse::Button::Left) == Window::Keystate::PRESSED)
        {
            int mouseX, mouseY;
            m_window.GetMousePos(mouseX, mouseY);
            if (mouseX >= 405 && mouseX <= 456 && mouseY >= 535 && mouseY <= 675)
            {
                Player_1_invisible.Field::Clear();
                Player_1_visible.Field::Clear();
                Player_2_invisible.Field::Clear();
                Player_2_visible.Field::Clear();
                return true;
            }
            if (mouseX >= 474 && mouseX <= 525 && mouseY >= 535 && mouseY <= 675)
            {
                return false;
            }
        }
    }
}

void Game::MainMenu()
{
    m_window.Clear();
    m_window.DrawBackground();
    m_window.DrawRect(sf::Vector2f(56, 45), sf::Vector2f(436, 215), sf::Color::Cyan);
    m_window.DrawRect(sf::Vector2f(83, 45), sf::Vector2f(423, 290), sf::Color::Cyan);
    m_window.DrawRect(sf::Vector2f(112, 45), sf::Vector2f(409, 365), sf::Color::Cyan);

    m_window.Window::DrawString(L"Выберите режим игры :", sf::Vector2f(347, 170), sf::Color::Black, 22);
    m_window.Window::DrawString(L"PvP", sf::Vector2f(446, 225), sf::Color::Black, 20);
    m_window.Window::DrawString(L"PvBOT", sf::Vector2f(433, 300), sf::Color::Black, 20);
    m_window.Window::DrawString(L"BOTvBOT", sf::Vector2f(419, 375), sf::Color::Black, 20);

    m_window.Display();
    while (!sf::Event::Closed)
    {
        m_window.PollEvents();
        if (m_window.GetKeyState(sf::Mouse::Button::Left) == Window::Keystate::PRESSED)
        {
            int mouseX, mouseY;
            m_window.GetMousePos(mouseX, mouseY);
            if (mouseX >= 436 && mouseX <= 492 && mouseY >= 215 && mouseY <= 260)
            {
                first = Player::Human;
                second = Player::Human;
                return;
            }
            else if (mouseX >= 423 && mouseX <= 506 && mouseY >= 290 && mouseY <= 335)
            {
                first = Player::Human;
                second = Player::Bot;
                return;
            }
            else if (mouseX >= 409 && mouseX <= 521 && mouseY >= 365 && mouseY <= 410)
            {
                first = Player::Bot;
                second = Player::Bot;
                return;
            }
        }
    }
}
