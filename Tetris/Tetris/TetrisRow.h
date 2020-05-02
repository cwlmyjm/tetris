#pragma once
#include <vector>

class TetrisRow
{
public:
	virtual ~TetrisRow() = default;

	virtual bool GetValue(int index) = 0;

	virtual void SetValue(int index, bool value) = 0;

	virtual bool AllTrue() = 0;
};