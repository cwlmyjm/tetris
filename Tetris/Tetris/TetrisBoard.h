#pragma once
#include <vector>
#include <fstream>
#include <iostream>

class TetrisRow;
class TetrisItem;

class TetrisBoard
{
public:
	TetrisBoard(int columns);
	~TetrisBoard();
	void PushItem(TetrisItem* item, int column);
	int GetScore();
	int GetHeightOfColumns(int column);
	void PrintCaseOnScreen(int id);
	void PrintCaseToFile(int id, std::fstream& file);

public:
	TetrisBoard();
	void ResetColumns(int columns);

private:
	void AddFourRows();
	bool CanPutItem(TetrisItem* itemData, int row, int colum);
	void PutItem(TetrisItem* itemData, int row, int colum);
	void CheckLineClear(int row, int lens);
	bool CheckInBoard(int row, int column);
	void PrintBoard();

private:
	std::vector<std::unique_ptr<TetrisRow>> m_board;
	int m_rowCount = 0;
	int m_columns = 0;
	int m_score = 0;

};

