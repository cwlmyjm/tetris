// Tetris.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "TetrisInterface.h"
#include "SyncSolution.h"
#include "AsyncSolution.h"
#include "AsyncSolutionEx.h"
#include "TetrisRow.h"
#include <Windows.h>

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
	int max_cost_time = 0;
	int min_cost_time = INT_MAX;
	int cost_time = 0;
	std::unique_ptr<TetrisInterface> solution = nullptr;
	//solution = std::make_unique<SyncSolution>();
	//solution = std::make_unique<AsyncSolution>();
	solution = std::make_unique<AsyncSolutionEx>();
	for (int i = 0; i < TEST_TIMES; i++)
	{
		cost_time = solution->tetris(i, INPUT, OUTPUT);
		max_cost_time = max(max_cost_time, cost_time);
		min_cost_time = min(min_cost_time, cost_time);
		total_cost_time += cost_time;
	}
	std::cout << "=========================" << std::endl;
	std::cout << "average time is " << total_cost_time / TEST_TIMES << "ms" << std::endl;
	std::cout << "maximum time is " << max_cost_time << "ms" << std::endl;
	std::cout << "minimum time is " << min_cost_time << "ms" << std::endl;
	TetrisRow::gc_clear();
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
