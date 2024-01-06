#include "Field.h"
#include <iostream>
#include <fstream>
#include <string>

Field::Field()
{

}
Field::~Field()
{

}

bool Field::LoadFromFile(const char* filepath)
{
	std::ifstream field(filepath);   // окрываем файл для чтения
	if (field.is_open())
	{
		for (int i = 0; i < 100; i++)
		{
			int temp;
			field >> temp;
			m_field[i] = (State)temp;
		}
		return true;
	}
	std::cout << L"Не удалось загрузить: " << filepath << std::endl;

	return false;
}
bool Field::LoadToFile(const char* filepath) const
{
	std::ofstream field(filepath);   // окрываем файл для чтения
	if (field.is_open())
	{
		for (int i = 0; i < 100; i++)
		{
			field << (int)m_field[i];
		}
		return true;
	}
	std::cout << L"Не удалось загрузить: " << filepath << std::endl;

	return false;
}

Field::State Field::GetState(int x, int y) const
{
	if (x < 0 || y < 0 || x > 9 || y > 9)
	{
		//std::cout << "[GAME WARNING] out of bounds get!:" << " {" << x << "," << y << "}" << std::endl;
		return Field::State::EMPTY;
	}
	

	return m_field[SubToInd(x, y)];
}

void Field::SetState(State s, int x, int y)
{
	if (x >= 0 && x <= 9 && y >= 0 && y <= 9)
	{
		m_field[SubToInd(x, y)] = s;
	}
	else
	{
		//std::cout << "[GAME WARNING] out of bounds Set!;" << " {" << x << "," << y << "}" << std::endl;
	}
}

void Field::Print() const
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			std::cout << (int)m_field[SubToInd(j, i)] << " ";
		std::cout << std::endl;
	}
}

void Field::Clear()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SetState(State::EMPTY, i, j);
		}
	}
}

int Field::SubToInd(int x, int y) const
{
	return y * 10 + x;
}
