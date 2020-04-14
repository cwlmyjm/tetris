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
	int a = index >> 3;
	int b = index & 0b111;

	return m_data[a] & (0b1 << b);
}

void MyBitVector::SetValue(int index, bool value)
{
	int a = index >> 3;
	int b = index & 0b111;

	if (value)
	{
		m_total++;
		m_data[a] |= (0b1 << b);
	}
}

bool MyBitVector::AllTrue()
{
	return m_total == m_size;
}
