#pragma once
#include "TetrisInterface.h"
#include <vector>
#include <tuple>

class SingleDataEx
{
public:
	SingleDataEx(int _index, int _columns, int _caseCount)
		: index(_index)
		, columns(_columns)
		, data(_caseCount)
	{}
	int index = 0;
	int columns = 0;
	std::vector<std::tuple<char, int, int>> data;
};

class AsyncSolutionEx : 
	public TetrisInterface
{
public:
	AsyncSolutionEx() = default;
	~AsyncSolutionEx() = default;

public:
	virtual int tetris(int index, const std::string& input_path, const std::string& output_path) override;

};

