#include "BitVector.h"
#include <algorithm>

BitVector::BitVector(int size)
	: m_size(size)
{
	m_data = std::vector<bool>(m_size, false);
}

BitVector::~BitVector()
{

}

bool BitVector::GetValue(int index)
{
	return m_data[index];
}

void BitVector::SetValue(int index, bool value)
{
	if (value)
	{
		m_total++;
		m_data[index] = value;
	}
}

bool BitVector::AllTrue()
{
	return m_total == m_size;
}

void BitVector::ClearData()
{
	m_total = 0;
	m_data = std::vector<bool>(m_size, false);
}