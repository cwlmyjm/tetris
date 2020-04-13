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
	m_data[index] = value;
}

bool BitVector::AllTrue()
{
	return std::all_of(m_data.cbegin(), m_data.cend(), [](bool value) {return value; });
}
