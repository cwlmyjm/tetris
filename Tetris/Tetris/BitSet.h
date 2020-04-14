#pragma once
#include "TetrisRow.h"
#include <unordered_set>

class BitSet :
	public TetrisRow
{
public:
	BitSet(int size);

	~BitSet();

	virtual bool GetValue(int index);

	virtual void SetValue(int index, bool value);

	virtual bool AllTrue();

private:
	std::unordered_set<int> m_data;
	int m_size = 0;
	int m_total = 0;

};

