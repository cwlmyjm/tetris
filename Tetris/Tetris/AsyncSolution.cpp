#include "AsyncSolution.h"
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

//#define MULTI_SEND
#define PROCESS_THREADS_COUNT 8

int AsyncSolution::tetris(int index, const std::string& input_path, const std::string& output_path)
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
	std::queue<SingleData*> datas;
	bool no_more_data = false;
	std::mutex lock;

	auto process_fun = [&]()
	{
		SingleData* data = nullptr;
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				std::lock_guard<std::mutex> lock_(lock);
				if (datas.empty())
				{
					if (no_more_data)
					{
						break;
					}
					continue;
				}
				else
				{
					data = datas.front();
					datas.pop();
				}
			}

			auto board = new TetrisBoard();
			board->ResetColumns(data->columns);
			for (const auto& data : data->data)
			{
				auto& item = TetrisItem::GetTetrisItem((TetrisItemType)std::get<0>(data), (TetrisItemRotation)std::get<2>(data));
				board->PushItem(&item, std::get<1>(data));
			}

			boards[data->index] = board;
			delete data;
		}
	};

	std::vector<std::thread> process_threads;
	for (int i = 0; i < PROCESS_THREADS_COUNT; i++)
	{
		process_threads.emplace_back(process_fun);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	{
#ifdef MULTI_SEND
		std::queue<SingleData*> temps;
#endif
		for (int i = 0; i < caseCount; i++)
		{
			// << read from file
			int columns = 0;
			int cubeCount = 0;
			input.read(columns, cubeCount);
			auto data = new SingleData(i, columns, cubeCount);
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

#ifdef MULTI_SEND
			temps.emplace(data);

#define TEMPS_MAX_SIZE 0b111
			if ((i & TEMPS_MAX_SIZE) == TEMPS_MAX_SIZE)
			{
				std::lock_guard<std::mutex> lock_(lock);
				while (temps.size())
				{
					datas.emplace(std::move(temps.front()));
					temps.pop();
				}
			}
#else
			{
				std::lock_guard<std::mutex> lock_(lock);
				datas.emplace(data);
			}
#endif
		}

		{
			std::lock_guard<std::mutex> lock_(lock);
#ifdef MULTI_SEND
			while (temps.size())
			{
				datas.emplace(std::move(temps.front()));
				temps.pop();
			}
#endif
			no_more_data = true;
		}
	};

	auto read_end = clock();

	for (int i = 0; i < PROCESS_THREADS_COUNT; i++)
	{
		process_threads[i].join();
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
