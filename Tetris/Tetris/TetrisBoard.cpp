#include "TetrisBoard.h"
#include "TetrisRow.h"
#include "BitSet.h"
#include "BitVector.h"
#include "MyBitVector.h"
#include "MixedBitVector.h"
#include "TetrisItem.h"

#define Threshold 1000
#define RowBelowThreshold MyBitVector
#define RowOverThreshold MixedBitVector

static int bonus_array[5] = { 0, 100, 250, 400,1000 };

TetrisBoard::TetrisBoard(int columns)
	: m_columns(columns)
{
	m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	m_rowCount = 4;
}


TetrisBoard::~TetrisBoard()
{
	for (auto& it : m_board)
	{
		delete it;
	}
}

void TetrisBoard::PushItem(TetrisItem* item, int column)
{
	int row = m_rowCount - 1;
	int targetRow = m_rowCount - 1;
	BoardDataReverseIterator rit = m_board.rbegin();
	BoardDataReverseIterator targetRit = m_board.rbegin();
	if (CanPutItem(item, row, rit, column))
	{
		do {
			targetRow = row--;
			targetRit = rit++;
		} while (CanPutItem(item, row, rit, column));
		PutItem(item, targetRow, targetRit, column);
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
	int i = 0;
	for (auto it = m_board.rbegin(); it != m_board.rend(); it++, i++)
	{
		if ((*it)->GetValue(column))
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

TetrisBoard::TetrisBoard()
{

}

void TetrisBoard::ResetColumns(int columns)
{
	m_columns = columns;
	m_board.clear();
	m_score = 0;

	m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	m_rowCount = 4;
}

void TetrisBoard::AddFourRows()
{
	if (m_rowCount < Threshold)
	{
		m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
		m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
		m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
		m_board.push_back(std::move(new (RowBelowThreshold)(m_columns)));
	}
	else
	{
		m_board.push_back(std::move(new (RowOverThreshold)(m_columns)));
		m_board.push_back(std::move(new (RowOverThreshold)(m_columns)));
		m_board.push_back(std::move(new (RowOverThreshold)(m_columns)));
		m_board.push_back(std::move(new (RowOverThreshold)(m_columns)));
	}
	m_rowCount += 4;
}

bool TetrisBoard::CanPutItem(TetrisItem* item, int row, BoardDataReverseIterator row_rit, int colum)
{
	auto rect = item->GetRect();
	for (int i = 0; i < rect.first; i++, row_rit++)
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

			auto boardElementStatus = (*row_rit)->GetValue(colum + j);// 这里对应一下。
			if (itemElement && boardElementStatus)
			{
				return false;
			}
		}
	}
	return true;
}

void TetrisBoard::PutItem(TetrisItem* item, int row, BoardDataReverseIterator row_rit, int colum)
{
	auto origin_rit = row_rit;
	auto rect = item->GetRect();
	for (int i = 0; i < rect.first; i++, row_rit++)
	{
		for (int j = 0; j < rect.second; j++)
		{
			bool itemElement = item->GetValue(i, j);
			if (!CheckInBoard(row - i, colum + j))
			{
				continue;
			}
			(*row_rit)->SetValue(colum + j, (*row_rit)->GetValue(colum + j) || itemElement);// 这里对应一下。
		}
	}

	CheckLineClear(row, origin_rit, rect.first);
	//PrintBoard();
}

void TetrisBoard::CheckLineClear(int row, BoardDataReverseIterator row_rit, int lens)
{
	BoardDataIterator row_it = (++row_rit).base();
	int clearLines = 0;
	for (int i = 0; i < lens; i++, row_it--)
	{
		auto& rowData = *row_it;
		if (rowData->AllTrue())
		{
			auto it = row_it;
			{
				rowData->ClearData();
				m_board.push_back(rowData);
			}
			m_board.erase(row_it);
			clearLines++;
		}
	}
	m_score += bonus_array[clearLines];
}

bool TetrisBoard::CheckInBoard(int row, int column)
{
	return 0 <= row && row < m_rowCount
		&& 0 <= column && column < m_columns;
}

void TetrisBoard::PrintBoard()
{
	for (auto it = m_board.rbegin(); it != m_board.rend(); it++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			std::cout << ((*it)->GetValue(j) ? 1 : 0);
		}
		std::cout << std::endl;
	}
	system("pause");
}

