#include "MyBitVector.h"

MyBitVector::MyBitVector(int size)
	: m_size(size)
{
	int count = m_size / 8;
	if (m_size % 8) count += 1;

	m_data = new char[count];
	memset(m_data, 0, count);
}

MyBitVector::~MyBitVector()
{
	delete[] m_data;
}

bool MyBitVector::GetValue(int index)
{
	int a = index / 8;
	int b = index % 8;

	return m_data[a] & (0b1 << b);
}

void MyBitVector::SetValue(int index, bool value)
{
	int a = index / 8;
	int b = index % 8;

	if (value)
	{
		m_data[a] |= (0b1 << b);
	}
	else
	{
		m_data[a] &= ~(0b1 << b);
	}
}

bool MyBitVector::AllTrue()
{
	for (int i = 0; i < m_size; i++)
	{
		if (!GetValue(i))
		{
			return false;
		}
	}
	return true;
}
