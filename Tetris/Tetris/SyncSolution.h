#pragma once
#include "TetrisInterface.h"
class SyncSolution :
	public TetrisInterface
{
public:
	SyncSolution() = default;
	~SyncSolution() = default;

public:
	virtual int tetris(int index, const std::string& input_path, const std::string& output_path) override;

};

