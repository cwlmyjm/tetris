#pragma once
#include <list>
#include <fstream>
#include <iostream>

class TetrisRow;
class TetrisItem;

typedef std::list<TetrisRow*> BoardData;
typedef std::list<TetrisRow*>::iterator BoardDataIterator;
typedef std::list<TetrisRow*>::reverse_iterator BoardDataReverseIterator;

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
	bool CanPutItem(TetrisItem* itemData, BoardDataReverseIterator row_rit, int colum);
	void PutItem(TetrisItem* itemData, BoardDataReverseIterator& row_rit, int colum);
	void CheckLineClear(BoardDataReverseIterator& row_rit, int lens);
	bool CheckInBoard(BoardDataReverseIterator& row_rit, int column);
	void PrintBoard();

private:
	BoardData m_board;
	int m_rowCount = 0;
	int m_columns = 0;
	int m_score = 0;

};

