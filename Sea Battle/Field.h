#pragma once
#include <array>

class Field
{
public:
	enum class State
	{
		EMPTY,
		SHIP,
		MISS,
		HIT
	};

	Field();
	~Field();

	bool LoadFromFile(const char* filepath);
	bool LoadToFile(const char* filepath) const;
	
	State GetState(int x, int y) const;
	void SetState(State s, int x, int y);

	void Print() const;
	void Clear();

private:
	int SubToInd(int x, int y) const;
	std::array<State, 100> m_field{ State::EMPTY };

};
