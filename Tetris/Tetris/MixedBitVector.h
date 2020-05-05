#pragma once
#include "TetrisRow.h"
#include <unordered_set>
#include <vector>

class MixedBitVector :
	public TetrisRow
{
public:
	MixedBitVector(int size);

	~MixedBitVector();

	virtual bool GetValue(int index);

	virtual void SetValue(int index, bool value);

	virtual bool AllTrue();

	virtual void ClearData();

private:
	std::unordered_set<int> m_data_set;
	std::vector<bool> m_data_vector;
	int m_size = 0;
	int m_total = 0;
	bool m_use_set = true;

};

