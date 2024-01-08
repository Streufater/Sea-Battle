#pragma once
#include "Field.h"
#include <iostream>


enum class ShotResult
{
	HIT,
	MISS,
	DEAD
};

class BotAction
{
public:
	BotAction() {}
	virtual ~BotAction() {}

	virtual void MakeTurn(unsigned int& x, unsigned int& y, ShotResult LastHit, const Field& field) = 0;
	virtual void Init() = 0;
};

class FirstBotAction : public BotAction
{
	struct Coords
	{
		unsigned int x;
		unsigned int y;
	};
public:

	virtual void MakeTurn(unsigned int& x, unsigned int& y, ShotResult LastHit, const Field& field) override
	{
		if (LastHit == ShotResult::HIT)
		{
			m_BotFlag = true;
		}
		else if (LastHit == ShotResult::DEAD)
		{
			m_BotFlag = false;
		}

		if (m_BotFlag == false)
		{
			while (true)
			{
				if (!m_HalfField)
				{
					if (turn == 100)
					{
						turn = 0;
						m_HalfField = true;
						break;
					}
						
					if (turn / 10 == 0 || turn / 10 == 2 || turn / 10 == 4 || turn / 10 == 6 || turn / 10 == 8)
					{
						x = turn % 10;
						y = turn / 10;
						turn++;
						turn++;
					}
					else
					{
						x = (turn + 1) % 10;
						y = (turn + 1) / 10;
						turn++;
						turn++;
					}
				}
				else
				{
					if (turn / 10 == 1 || turn / 10 == 3 || turn / 10 == 5 || turn / 10 == 7 || turn / 10 == 9)
					{
						x = turn % 10;
						y = turn / 10;
						turn++;
						turn++;
					}
					else
					{
						x = (turn + 1) % 10;
						y = (turn + 1) / 10;
						turn++;
						turn++;
					}
				}
				if (field.GetState(x, y) == Field::State::EMPTY)
				{
					return;
				}
			}
		}
		else if (m_BotFlag == true)
		{

			for (int i = 0; i < 4; i++)
			{
				if (!m_HalfField)
				{
					if ((turn - 2) / 10 == 0 || (turn - 2) / 10 == 2 || (turn - 2) / 10 == 4 || (turn - 2) / 10 == 6 || (turn - 2) / 10 == 8)
					{
						x = (turn - 2) % 10;
						y = (turn - 2) / 10;
					}
					else
					{
						x = (turn - 2 + 1) % 10;
						y = (turn - 2 + 1) / 10;
					}
				}
				else
				{
					if ((turn - 2) / 10 == 1 || (turn - 2) / 10 == 3 || (turn - 2) / 10 == 5 || (turn - 2) / 10 == 7 || (turn - 2) / 10 == 9)
					{
						x = (turn - 2) % 10;
						y = (turn - 2) / 10;
					}
					else
					{
						x = (turn - 2 + 1) % 10;
						y = (turn - 2 + 1) / 10;
					}
				}

				Coords DirectionsOfShot[4]{ {1,0}, {-1,0}, {0,1}, {0,-1} };
				Field::State cell = Field::State::EMPTY;
				for (int j = 0; j < 3; j++)
				{

					x = x + DirectionsOfShot[i].x;
					y = y + DirectionsOfShot[i].y;
					Field::State cell = field.GetState(x, y);
					if (cell == Field::State::EMPTY && x >= 0 && x <= 9 && y >= 0 && y <= 9)
					{
						return;
					}

					if (cell == Field::State::MISS)
					{
						break;
					}
				}
			}
		}
	}

	virtual void Init() override
	{
		turn = 0;
		m_BotFlag = false;
		m_HalfField = false;
	}

private:
	unsigned int turn = 0;
	bool m_BotFlag = false;
	bool m_HalfField = false;
};

class SecondBotAction : public BotAction
{
	struct Coords
	{
		unsigned int x;
		unsigned int y;
	};
public:

	virtual void MakeTurn(unsigned int& x, unsigned int& y, ShotResult LastHit, const Field& field) override
	{	
		if (LastHit == ShotResult::HIT)
		{
			m_BotFlag = true;
		}
		else if(LastHit == ShotResult::DEAD)
		{
			m_BotFlag = false;
		}

		if (m_BotFlag == false)
		{
			while (true)
			{
				if (!m_HalfField)
				{
					if (turn == 100)
					{
						turn = 0;
						m_HalfField = true;
						break;
					}

					if (turn / 10 == 0 || turn / 10 == 2 || turn / 10 == 4 || turn / 10 == 6 || turn / 10 == 8)
					{
						x = (turn + 1) % 10;
						y = (turn + 1) / 10;
						turn++;
						turn++;
					}
					else
					{
						x = turn % 10;
						y = turn / 10;
						turn++;
						turn++;
					}
				}
				else
				{
					if (turn / 10 == 1 || turn / 10 == 3 || turn / 10 == 5 || turn / 10 == 7 || turn / 10 == 9)
					{
						x = (turn + 1) % 10;
						y = (turn + 1) / 10;
						turn++;
						turn++;
					}
					else
					{
						x = turn % 10;
						y = turn / 10;
						turn++;
						turn++;
					}
				}
				if (field.GetState(x, y) == Field::State::EMPTY)
				{
					return;
				}
			}
		}
		else if (m_BotFlag == true)
		{
			for (int i = 0; i < 4; i++)
			{
				if (!m_HalfField)
				{
					if ((turn - 2) / 10 == 0 || (turn - 2) / 10 == 2 || (turn - 2) / 10 == 4 || (turn - 2) / 10 == 6 || (turn - 2) / 10 == 8)
					{
						x = (turn - 2 + 1) % 10;
						y = (turn - 2 + 1) / 10;
					}
					else
					{
						x = (turn - 2) % 10;
						y = (turn - 2) / 10;
					}
				}
				else
				{
					if ((turn - 2) / 10 == 1 || (turn - 2) / 10 == 3 || (turn - 2) / 10 == 5 || (turn - 2) / 10 == 7 || (turn - 2) / 10 == 9)
					{
						x = (turn - 2 + 1) % 10;
						y = (turn - 2 + 1) / 10;
					}
					else
					{
						x = (turn - 2) % 10;
						y = (turn - 2) / 10;
					}
				}

				Coords DirectionsOfShot[4]{ {1,0}, {-1,0}, {0,1}, {0,-1} };
				Field::State cell = Field::State::EMPTY;
				for (int j = 0; j < 3; j++)
				{

					x = x + DirectionsOfShot[i].x;
					y = y + DirectionsOfShot[i].y;
					Field::State cell = field.GetState(x, y);
					if (cell == Field::State::EMPTY && x >= 0 && x <= 9 && y >= 0 && y <= 9)
					{
						return;
					}
					
					if (cell == Field::State::MISS)
					{
						break;
					}
				}
			}
		}
	}

	virtual void Init() override
	{
		turn = 0;
		m_BotFlag = false;
		m_HalfField = false;
	}

private:
	unsigned int turn = 0;
	bool m_BotFlag = false;
	bool m_HalfField = false;
};
