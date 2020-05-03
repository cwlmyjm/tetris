// Tetris.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
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
#include "MyMutex.h"

class SingleData
{
public:
	SingleData(int _index, int _columns, int _caseCount) 
		: index(_index)
		, columns(_columns)
		, data(_caseCount)
	{}
	int index = 0;
	int columns = 0;
	std::vector<std::tuple<char, int, int>> data;
};

int tetris(int index, const std::string& input_path, const std::string& output_path)
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

#if 0
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

#else

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

	const int process_threads_count = 4;
	std::vector<std::thread> process_threads;
	for (int i = 0; i < process_threads_count; i++)
	{
		process_threads.emplace_back(process_fun);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	{
		std::queue<SingleData*> temps;
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
		}

		{
			std::lock_guard<std::mutex> lock_(lock);
			while (temps.size())
			{
				datas.emplace(std::move(temps.front()));
				temps.pop();
			}
			no_more_data = true;
		}
	};

	auto read_end = clock();

	for (int i = 0; i < process_threads_count; i++)
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
#endif

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

int main()
{
#define TEST_TIMES 100

#define TEST_4
#ifdef TEST_1
#define INPUT "./test_input.txt"
#define OUTPUT "./test_output.txt"
#endif
#ifdef TEST_2
#define INPUT "./small_input.txt"
#define OUTPUT "./small_output.txt"
#endif
#ifdef TEST_3
#define INPUT "./medium_input.txt"
#define OUTPUT "./medium_output.txt"
#endif
#ifdef TEST_4
#define INPUT "./big_input.txt"
#define OUTPUT "./big_output.txt"
#endif
#ifdef TEST_5
#define INPUT "./huge_input.txt"
#define OUTPUT "./huge_output.txt"
#endif

	int total_cost_time = 0;
	for (int i = 0; i < TEST_TIMES; i++)
	{
		total_cost_time += tetris(i, INPUT, OUTPUT);
	}
	std::cout << "=========================" << std::endl;
	std::cout << "average time is " << total_cost_time / TEST_TIMES << "ms" << std::endl;
	system("pause");
	return 0;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
