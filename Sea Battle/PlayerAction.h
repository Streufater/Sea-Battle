#pragma once
#include "Field.h"

class PlayerAction
{
public:
	PlayerAction() {}
	virtual ~PlayerAction() {}

	virtual Coords MakeTurn(bool prevHit, const Field& field) = 0;

private:
};



class AIPlayerAction : public PlayerAction
{
public:
	AIPlayerAction() {}
	virtual ~AIPlayerAction() {}

	virtual Coords MakeTurn(bool prevHit, const Field& field) override
	{

	}


private:

};


class GUIPlayerAction : public PlayerAction
{
public:
	GUIPlayerAction() {}
	virtual ~GUIPlayerAction() {}

	virtual Coords MakeTurn(bool prevHit, const Field& field) override
	{

	}


private:

};
