#pragma once
#include "Field.h"

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
};

class StupidBotAction : public BotAction
{
public:

	virtual void MakeTurn(unsigned int& x, unsigned int& y, ShotResult LastHit, const Field& field) override
	{
		bool nice = false;

		while (!nice)
		{
			x = turn % 10;
			y = turn / 10;

			if (field.GetState(x, y) == Field::State::EMPTY)
			{
				nice = true;
			}

			turn++;
		}

	}

private:
	unsigned int turn = 0;
};

class SmartBotAction : public BotAction
{
public:

	virtual void MakeTurn(unsigned int& x, unsigned int& y, ShotResult LastHit, const Field& field) override
	{
		bool nice = false;

		while (!nice)
		{
			x = turn / 10;
			y = turn % 10;

			if (field.GetState(x, y) == Field::State::EMPTY)
			{
				nice = true;
			}

			turn++;
		}

	}

private:
	unsigned int turn = 0;
};
