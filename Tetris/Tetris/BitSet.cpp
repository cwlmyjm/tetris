#include "BitSet.h"

BitSet::BitSet(int size)
	: m_size(size)
{
}

BitSet::~BitSet()
{

}

bool BitSet::GetValue(int index)
{
	return m_data.find(index) != m_data.cend();
}

void BitSet::SetValue(int index, bool value)
{
	if (value)
	{
		m_total++;
		m_data.insert(index);
	}
}

bool BitSet::AllTrue()
{
	return m_total == m_size;
}

void BitSet::ClearData()
{
	m_total = 0;
	m_data.clear();
}
