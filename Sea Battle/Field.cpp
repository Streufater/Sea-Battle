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
	std::ifstream field(filepath);   // �������� ���� ��� ������
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
	std::cout << "�� ������� ���������: " << filepath << std::endl;

	return false;
}

Field::State Field::GetState(int x, int y)
{
	if (x < 0 || y < 0 || x > 9 || y > 9)
		return Field::EMPTY;

	return m_field[SubToInd(x, y)];
}

void Field::SetState(State s, int x, int y)
{
	if (x >= 0 && x <= 9 && y >= 0 && y <= 9)
	m_field[SubToInd(x, y)] = s;
}

void Field::Print()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			std::cout << m_field[SubToInd(j, i)] << " ";
		std::cout << std::endl;
	}
}

int Field::SubToInd(int x, int y)
{
	return y * 10 + x;
}
