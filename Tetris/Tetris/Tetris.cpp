// Tetris.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "TetrisBoard.h"
#include "TetrisItem.h"
#include <fstream>
#include <iostream>
#include <time.h>

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
	std::fstream input("./big_input.txt", fstream::in);
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
	for (int i = 0; i < caseCount; i++)
	{
		// << read from file
		int columns = 0;
		int cubeCount = 0;
		input >> columns;
		input >> cubeCount;
		auto board = new TetrisBoard(columns);
		for (int j = 0; j < cubeCount; j++)
		{
			char type = 'I';
			int column = 0;
			int rotation = 0;
			input >> type;
			input >> column;
			input >> rotation;
			auto& item = TetrisItem::GetTetrisItem((TetrisItemType)type, (TetrisItemRotation)rotation);
			board->PushItem(&item, column);
		}
		//board->PrintCaseOnScreen(i);
		//board->PrintCaseToFile(i, output);
		total += board->GetScore();
		delete board;
	}

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
