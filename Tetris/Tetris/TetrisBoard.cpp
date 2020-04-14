#include "TetrisBoard.h"
#include "TetrisRow.h"
#include "BitSet.h"
#include "BitVector.h"
#include "MyBitVector.h"
#include "MixedBitVector.h"
#include "TetrisItem.h"

#define Row MixedBitVector

TetrisBoard::TetrisBoard(int columns)
	: m_columns(columns)
{
	m_rowCount = 4;
	m_board.push_back(std::move(std::make_shared<Row>(m_columns)));
	m_board.push_back(std::move(std::make_shared<Row>(m_columns)));
	m_board.push_back(std::move(std::make_shared<Row>(m_columns)));
	m_board.push_back(std::move(std::make_shared<Row>(m_columns)));
}


TetrisBoard::~TetrisBoard()
{
}

void TetrisBoard::PushItem(TetrisItem* item, int column)
{
	int row = m_rowCount - 1;
	int targetRow = m_rowCount - 1;
	if (CanPutItem(item, row, column))
	{
		while (CanPutItem(item, row, column))
		{
			targetRow = row;
			row--;
		};
		PutItem(item, targetRow, column);
	}
	else
	{
		AddFourRows();
		PushItem(item, column);
	}
}


int TetrisBoard::GetScore()
{
	return m_score;
};

int TetrisBoard::GetHeightOfColumns(int column)
{
	for (int i = 0; i < m_rowCount; i++)
	{
		int index = m_rowCount - 1 - i;
		if (m_board[index]->GetValue(column))
		{
			return m_rowCount - i;
		}
	}
	return 0;
};

void TetrisBoard::PrintCaseOnScreen(int id)
{
	std::cout << "Case " << id << ":" << m_score << std::endl;
	for (int i = 0; i < m_columns; i++)
	{
		std::cout << GetHeightOfColumns(i) << ",";
	}
	std::cout << std::endl;
	//PrintBoard();
};

void TetrisBoard::PrintCaseToFile(int id, fstream& file)
{
	file << "Case " << id << ":" << m_score << std::endl;
	for (int i = 0; i < m_columns; i++)
	{
		file << GetHeightOfColumns(i) << ",";
	}
	file << std::endl;
	//PrintBoard();
}

void TetrisBoard::AddFourRows()
{
	m_rowCount += 4;
	m_board.push_back(std::move(std::make_shared<Row>(m_columns)));
	m_board.push_back(std::move(std::make_shared<Row>(m_columns)));
	m_board.push_back(std::move(std::make_shared<Row>(m_columns)));
	m_board.push_back(std::move(std::make_shared<Row>(m_columns)));
}

bool TetrisBoard::CanPutItem(TetrisItem* item, int row, int colum)
{
	auto rect = item->GetRect();
	for (int i = 0; i < rect.first; i++)
	{
		for (int j = 0; j < rect.second; j++)
		{
			bool itemElement = item->GetValue(i, j);
			// 向下超出了
			if (row - i < 0)
			{
				return false;
			}

			if (!CheckInBoard(row - i, colum + j))
			{
				continue;
			}

			auto boardElementStatus = m_board[row - i]->GetValue(colum + j);// 这里对应一下。
			if (itemElement && boardElementStatus)
			{
				return false;
			}
		}
	}
	return true;
}

void TetrisBoard::PutItem(TetrisItem* item, int row, int colum)
{
	auto rect = item->GetRect();
	for (int i = 0; i < rect.first; i++)
	{
		for (int j = 0; j < rect.second; j++)
		{
			bool itemElement = item->GetValue(i, j);
			if (!CheckInBoard(row - i, colum + j))
			{
				continue;
			}
			m_board[row - i]->SetValue(colum + j, m_board[row - i]->GetValue(colum + j) || itemElement);// 这里对应一下。
		}
	}

	CheckLineClear(row, rect.first);
	//PrintBoard();
}

void TetrisBoard::CheckLineClear(int row, int lens)
{
	int clearLines = 0;
	for (int i = 0; i < lens; i++)
	{
		int _row = row - i;
		auto& rowData = m_board[_row];
		//if (std::all_of(rowData.cbegin(), rowData.cend(), [](bool input) {return input; }))
		if (rowData->AllTrue())
		{
			m_board.erase(m_board.cbegin() + _row);
			clearLines++;
		}
	}

	m_rowCount -= clearLines;
	if (clearLines == 1)
	{
		m_score += 100;
	}
	else if (clearLines == 2)
	{
		m_score += 250;
	}
	else if (clearLines == 3)
	{
		m_score += 400;
	}
	else if (clearLines == 4)
	{
		m_score += 1000;
	}
}

bool TetrisBoard::CheckInBoard(int row, int column)
{
	return 0 <= row && row < m_rowCount
		&& 0 <= column && column < m_columns;
}

void TetrisBoard::PrintBoard()
{
	for (int i = 0; i < m_rowCount; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			std::cout << (m_board[m_rowCount - 1 - i]->GetValue(j) ? 1 : 0);
		}
		std::cout << std::endl;
	}
	system("pause");
}

