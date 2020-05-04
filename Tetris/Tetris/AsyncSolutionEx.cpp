#include "AsyncSolutionEx.h"
#include "TetrisBoard.h"
#include "TetrisItem.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <mutex>
#include <queue>
#include <thread>
#include "MyFstream.h"
#include "StdFstream.h"
#include "SuperFstream.h"
#include "TaskThread.h"

#define PROCESS_THREADS_COUNT 8

int AsyncSolutionEx::tetris(int index, const std::string& input_path, const std::string& output_path)
{
	auto begin = clock();

	TetrisItem::InitTetrisItemsMap();

	//StdFstream input(input_path.c_str(), fstream::in);
	//MyFstream input(input_path.c_str(), "r");
	SuperFstream input(input_path.c_str(), "r");
	StdFstream output(output_path.c_str(), fstream::out);

	if (!input.is_open())
	{
		return 0;
	}

	// << read from file
	int caseCount = 0;
	input >> caseCount;
	int total = 0;

	std::vector<TetrisBoard*> boards(caseCount, nullptr);
	std::vector<std::shared_ptr<TaskThread>> task_thread_pool(PROCESS_THREADS_COUNT, nullptr);
	for (auto& task_thread : task_thread_pool)
	{
		task_thread = std::move(std::make_shared<TaskThread>(true));
	}
	int current_post_index = 0;

	auto process_fun = [&](SingleDataEx* data)
	{
		auto board = new TetrisBoard();
		board->ResetColumns(data->columns);
		for (const auto& data : data->data)
		{
			auto& item = TetrisItem::GetTetrisItem((TetrisItemType)std::get<0>(data), (TetrisItemRotation)std::get<2>(data));
			board->PushItem(&item, std::get<1>(data));
		}

		boards[data->index] = board;
		delete data;
	};

	{
		for (int i = 0; i < caseCount; i++)
		{
			// << read from file
			int columns = 0;
			int cubeCount = 0;
			input.read(columns, cubeCount);
			auto data = new SingleDataEx(i, columns, cubeCount);
			for (int j = 0; j < cubeCount;)
			{
#define SIZE 4
#if SIZE > 1
				if (j + SIZE < cubeCount)
				{
					char type[SIZE];
					int column[SIZE];
					int rotation[SIZE];
					input.readN<SIZE>(type, column, rotation);
					for (int i = 0; i < SIZE; i++)
					{
						data->data[j + i] = std::move(std::make_tuple(type[i], column[i], rotation[i]));
					}
					j += SIZE;
				}
				else
#endif
				{
					char type = 'I';
					int column = 0;
					int rotation = 0;
					input.read(type, column, rotation);
					data->data[j] = std::move(std::make_tuple(type, column, rotation));
					j += 1;
				}
			}

			// 投递任务给子线程
			{
				auto task = std::bind(process_fun, data);
				task_thread_pool[current_post_index]->PostTask(task);
				current_post_index = (current_post_index + 1) & (PROCESS_THREADS_COUNT - 1);
			}
		}
	};

	auto read_end = clock();

	// 等待所以子线程结束任务
	for (auto& task_thread : task_thread_pool)
	{
		task_thread->NotifyNoMoreTask();
	}

	for (auto& task_thread : task_thread_pool)
	{
		task_thread->Wait();
	}

	for (auto& board : boards)
	{
		//board->PrintCaseOnScreen(i);
		//board->PrintCaseToFile(i, output);
		total += board->GetScore();
		delete board;
	}

	auto end = clock();

	// 输出时间消耗等信息
	std::cout << "=========================" << index << std::endl;
	auto read_cost_time = read_end - begin;
	std::cout << "read time is " << read_cost_time << "ms" << std::endl;
	output << "read time is " << read_cost_time << "ms" << std::endl;

	auto cost_time = end - begin;
	std::cout << "cost time is " << cost_time << "ms" << std::endl;
	output << "cost time is " << cost_time << "ms" << std::endl;

	auto calc_cost_time = end - read_end;
	std::cout << "calc time is " << calc_cost_time << "ms" << std::endl;
	output << "calc time is " << calc_cost_time << "ms" << std::endl;

	std::cout << "total score is " << total << std::endl;

	input.close();
	output.close();

	return cost_time;
}
