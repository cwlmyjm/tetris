#include "SyncSolution.h"
#include <iostream>
#include "TetrisBoard.h"
#include "TetrisItem.h"
#include <time.h>
#include "MyFstream.h"
#include "StdFstream.h"

int SyncSolution::tetris(int index, const std::string& input_path, const std::string& output_path)
{
	auto begin = clock();

	TetrisItem::InitTetrisItemsMap();

	//StdFstream input(input_path.c_str(), fstream::in);
	MyFstream input(input_path.c_str(), "r");
	StdFstream output(output_path.c_str(), fstream::out);

	if (!input.is_open())
	{
		return 0;
	}

	// << read from file
	int caseCount = 0;
	input >> caseCount;
	int total = 0;

	auto board = std::make_unique<TetrisBoard>();
	for (int i = 0; i < caseCount; i++)
	{
		// << read from file
		int columns = 0;
		int cubeCount = 0;
		char type = 'I';
		int column = 0;
		int rotation = 0;

		input.read(columns, cubeCount);
		board->ResetColumns(columns);
		for (int j = 0; j < cubeCount; j++)
		{
			input.read(type, column, rotation);
			auto& item = TetrisItem::GetTetrisItem((TetrisItemType)type, (TetrisItemRotation)rotation);
			board->PushItem(&item, column);
		}
		//board->PrintCaseOnScreen(i);
		//board->PrintCaseToFile(i, output);
		total += board->GetScore();
	}

	auto end = clock();

	// 输出时间消耗等信息
	auto cost_time = end - begin;
	std::cout << "cost time is " << cost_time << "ms" << std::endl;
	output << "cost time is " << cost_time << "ms" << std::endl;

	std::cout << "total score is " << total << std::endl;

	input.close();
	output.close();

	return cost_time;
}
