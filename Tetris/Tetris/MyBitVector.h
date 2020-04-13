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

private:
	char* m_data = nullptr;
	int m_size = 0;

};

