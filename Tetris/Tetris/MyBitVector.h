#pragma once
#include "TetrisRow.h"
class MyBitVector :
	public TetrisRow
{
public:
	MyBitVector(int size);

	~MyBitVector();

	virtual bool GetValue(int index);

	virtual void SetValue(int index, bool value);

	virtual bool AllTrue();

	virtual void ClearData();

private:
	char* m_data = nullptr;
	int m_size = 0;
	int m_total = 0;
	int m_count = 0;

};

