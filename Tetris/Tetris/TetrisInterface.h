#pragma once
#include <string>

class TetrisInterface
{
public:
	virtual ~TetrisInterface() = default;
	virtual int tetris(int index, const std::string& input_path, const std::string& output_path) = 0;
};
