#pragma once
#include "TetrisRow.h"
#include <vector>

class BitVector :
	public TetrisRow
{
public:
	BitVector(int size);

	~BitVector();

	virtual bool GetValue(int index);

	virtual void SetValue(int index, bool value);

	virtual bool AllTrue();

private:
	std::vector<bool> m_data;
	int m_size = 0;
	int m_total = 0;

};

