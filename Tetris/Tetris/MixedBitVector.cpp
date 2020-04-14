#include "MixedBitVector.h"

MixedBitVector::MixedBitVector(int size)
	: m_size(size)
{
}

MixedBitVector::~MixedBitVector()
{

}

bool MixedBitVector::GetValue(int index)
{
	if (m_use_set)
	{
		return m_data_set.find(index) != m_data_set.cend();
	}
	else
	{
		return m_data_vector[index];
	}
}

void MixedBitVector::SetValue(int index, bool value)
{
	if (value)
	{
		m_total++;
		if (m_use_set)
		{
			m_data_set.insert(index);

			// 1 char  = 8bit			= 1 << 3
			// 1 short = 2char = 16bit  = 1 << 4
			// 1 int   = 4char = 32bit  = 1 << 5
			if ((m_total << 5) > m_size)
			{
				m_data_vector = std::vector<bool>(m_size, false);
				for (auto& index : m_data_set)
				{
					m_data_vector[index] = true;
				}
				m_data_set.clear();
				m_use_set = false;
			}
		}
		else
		{
			m_data_vector[index] = value;
		}
	}
}

bool MixedBitVector::AllTrue()
{
	return m_total == m_size;
}
