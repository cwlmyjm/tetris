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

class SingleData
{
public:
	int columns = 0;
	std::vector<std::pair<TetrisItem*, int>> data;
};

int tetris(const std::string& input_path, const std::string& output_path)
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

	std::vector<std::shared_ptr<TetrisBoard>> boards(caseCount, nullptr);
	std::queue<std::pair<int, std::shared_ptr<SingleData>>> datas;
	bool no_more_data = false;
	std::mutex lock;

	auto process_fun = [&]()
	{
		std::pair<int, std::shared_ptr<SingleData>> data;
		while (true)
		{
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5));
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
					data.swap(datas.front());
					datas.pop();
				}
			}

			auto board = std::make_shared<TetrisBoard>();
			board->ResetColumns(data.second->columns);
			for (const auto& p : data.second->data)
			{
				board->PushItem(p.first, p.second);
			}

			boards[data.first].swap(board);
		}
	};

	const int process_threads_count = 4;
	std::vector<std::thread> process_threads;
	for (int i = 0; i < process_threads_count; i++)
	{
		process_threads.emplace_back(process_fun);
	}

	{
		for (int i = 0; i < caseCount; i++)
		{
			// << read from file
			auto data = std::make_shared<SingleData>();
			int cubeCount = 0;
			input.read(data->columns, cubeCount);
			for (int j = 0; j < cubeCount; j++)
			{
				char type = 'I';
				int column = 0;
				int rotation = 0;
				input.read(type, column, rotation);
				auto& item = TetrisItem::GetTetrisItem((TetrisItemType)type, (TetrisItemRotation)rotation);
				data->data.emplace_back(&item, column);
			}

			{
				std::lock_guard<std::mutex> lock_(lock);
				datas.emplace(i, data);
			}
		}

		{
			std::lock_guard<std::mutex> lock_(lock);
			no_more_data = true;
		}
	};

	for (int i = 0; i < process_threads_count; i++)
	{
		process_threads[i].join();
	}

	for (auto& board : boards)
	{
		//board->PrintCaseOnScreen(i);
		//board->PrintCaseToFile(i, output);
		total += board->GetScore();
	}
#endif

	input.close();
	auto end = clock();
	auto cost_time = end - begin;
	std::cout << "total score is " << total << std::endl;
	std::cout << "time is " << cost_time << "ms" << std::endl;
	output << "time is " << cost_time << "ms" << std::endl;
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
		total_cost_time += tetris(INPUT, OUTPUT);
	}
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
