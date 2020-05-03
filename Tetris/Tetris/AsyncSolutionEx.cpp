#include "AsyncSolutionEx.h"
#include "TetrisBoard.h"
#include "TetrisItem.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <mutex>
#include <queue>
#include <thread>
#include <atomic>
#include "MyFstream.h"
#include "StdFstream.h"
#include "SuperFstream.h"

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
	std::condition_variable cv;
	std::mutex lock;
	std::atomic<int> alive_process_threads_count = 0;

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

		// 子线程任务结束，计数器减一，并发送notify唤醒主线程。
		alive_process_threads_count--;
		cv.notify_one();
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

			{
				// 如果子线程数量小于PROCESS_THREADS_COUNT，那么马上创建子线程。
				// 否则开始等待，直到有子线程结束时发送notify来唤醒。
				std::unique_lock<std::mutex> lock_(lock);
				cv.wait(lock_, [&]() {
					return alive_process_threads_count < PROCESS_THREADS_COUNT;
				});
				alive_process_threads_count++;
				std::thread process_task(process_fun, data);
				process_task.detach();
			}
		}
	};

	auto read_end = clock();

	// 等待所以子线程结束任务
	std::unique_lock<std::mutex> lock_(lock);
	while (alive_process_threads_count)
	{
		cv.wait(lock_);
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
