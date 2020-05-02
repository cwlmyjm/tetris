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

class SingleData
{
public:
	int columns;
	std::vector<std::pair<TetrisItem*, int>> data;
};

int main()
{
	auto begin = clock();

#define TEST_4

#ifdef TEST_1
	std::fstream input("./test_input.txt", fstream::in);
	std::fstream output("./test_output.txt", fstream::out);
#endif

#ifdef TEST_2
	std::fstream input("./small_input.txt", fstream::in);
	std::fstream output("./small_output.txt", fstream::out);
#endif

#ifdef TEST_3
	std::fstream input("./medium_input.txt", fstream::in);
	std::fstream output("./medium_output.txt", fstream::out);
#endif

#ifdef TEST_4
	//std::fstream input("./big_input.txt", fstream::in);
	MyFstream input("./big_input.txt", "r");
	std::fstream output("./big_output.txt", fstream::out);
#endif

#ifdef TEST_5
	std::fstream input("./huge_input.txt", fstream::in);
	std::fstream output("./huge_output.txt", fstream::out);
#endif

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

		//input >> columns >> cubeCount;
		input.read(columns, cubeCount);
		board->ResetColumns(columns);
		for (int j = 0; j < cubeCount; j++)
		{
			//input >> type >> column >> rotation;
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
			//input >> data->columns >> cubeCount;
			input.read(data->columns, cubeCount);
			for (int j = 0; j < cubeCount; j++)
			{
				char type = 'I';
				int column = 0;
				int rotation = 0;
				//input >> type >> column >> rotation;
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

	std::cout << "total score is " << total << std::endl;
	std::cout << "time is " << end - begin << "ms" << std::endl;
	output << "time is " << end - begin << "ms" << std::endl;
	output.close();

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
