#include "TetrisItem.h"
#include <assert.h>

std::array<TetrisItem, 28> TetrisItem::itemsMap;

TetrisItem& TetrisItem::GetTetrisItem(const TetrisItemType& type, const TetrisItemRotation& rotation)
{
	return itemsMap[TetrisItemTypeRotation2Int(type, rotation)];
}

void TetrisItem::InitTetrisItemsMap()
{
	static bool itemsMapHasInited = false;
	if (itemsMapHasInited)
	{
		return;
	}
	std::vector<TetrisItemType> types = { TetrisItemType::I, TetrisItemType::J, TetrisItemType::L, TetrisItemType::O, TetrisItemType::S, TetrisItemType::T, TetrisItemType::Z };
	std::vector<TetrisItemRotation> rotations = { TetrisItemRotation::R0, TetrisItemRotation::R90, TetrisItemRotation::R180, TetrisItemRotation::R270 };
	for (auto& type : types)
	{
		for (auto& rotation : rotations)
		{
			itemsMap[TetrisItemTypeRotation2Int(type, rotation)] = std::move(TetrisItem(type, rotation));
		}
	}
	itemsMapHasInited = true;
}

int TetrisItem::TetrisItemType2Int(const TetrisItemType& type)
{
	switch (type)
	{
	case TetrisItemType::I:
		return 0;
	case TetrisItemType::J:
		return 1;
	case TetrisItemType::L:
		return 2;
	case TetrisItemType::O:
		return 3;
	case TetrisItemType::S:
		return 4;
	case TetrisItemType::T:
		return 5;
	case TetrisItemType::Z:
		return 6;
	}
	assert(false);
	return 0;
}

int TetrisItem::TetrisItemRotation2Int(const TetrisItemRotation& rotation)
{
	switch (rotation)
	{
	case TetrisItemRotation::R0:
		return 0;
	case TetrisItemRotation::R90:
		return 1;
	case TetrisItemRotation::R180:
		return 2;
	case TetrisItemRotation::R270:
		return 3;
	}
	assert(false);
	return 0;
}

int TetrisItem::TetrisItemTypeRotation2Int(const TetrisItemType& type, const TetrisItemRotation& rotation)
{
	return TetrisItemType2Int(type) * 4 + TetrisItemRotation2Int(rotation);
}

TetrisItem::TetrisItem(TetrisItemType type, TetrisItemRotation rotation)
	: m_type(type), m_rotation(rotation)
{
	Init();
}

TetrisItem::TetrisItem(const TetrisItem& other)
{
	m_type = other.m_type;
	m_rotation = other.m_rotation;
	m_cube = other.m_cube;
	m_rows = other.m_rows;
	m_columns = other.m_columns;
}

TetrisItem::~TetrisItem()
{

}

bool TetrisItem::GetValue(int row, int column)
{
	int _row = row;
	int _column = column;
	switch (m_rotation)
	{
	case TetrisItemRotation::R0:
		break;
	case TetrisItemRotation::R90:
		_row = m_rows - 1 - column;
		_column = row;
		break;
	case TetrisItemRotation::R180:
		_row = m_rows - 1 - row;
		_column = m_columns - 1 - column;
		break;
	case TetrisItemRotation::R270:
		_row = column;
		_column = m_columns - 1 - row;
		break;
	default:
		break;
	}

	return m_cube[_row][_column];
}

pair<int, int> TetrisItem::GetRect()
{
	if (m_rotation == TetrisItemRotation::R0 || m_rotation == TetrisItemRotation::R180)
	{
		return std::make_pair(m_rows, m_columns);
	}
	else
	{
		return std::make_pair(m_columns, m_rows);
	}
}

void TetrisItem::Init()
{
	switch (m_type) {
	case TetrisItemType::I:
		m_cube.push_back({ true, true, true, true });
		m_rows = 1;
		m_columns = 4;
		break;
	case TetrisItemType::J:
		m_cube.push_back({ true, false, false });
		m_cube.push_back({ true, true, true });
		m_rows = 2;
		m_columns = 3;
		break;
	case TetrisItemType::L:
		m_cube.push_back({ false, false, true });
		m_cube.push_back({ true, true, true });
		m_rows = 2;
		m_columns = 3;
		break;
	case TetrisItemType::O:
		m_cube.push_back({ true, true });
		m_cube.push_back({ true, true });
		m_rows = 2;
		m_columns = 2;
		break;
	case TetrisItemType::S:
		m_cube.push_back({ false, true, true });
		m_cube.push_back({ true, true, false });
		m_rows = 2;
		m_columns = 3;
		break;
	case TetrisItemType::T:
		m_cube.push_back({ false, true, false });
		m_cube.push_back({ true, true, true });
		m_rows = 2;
		m_columns = 3;
		break;
	case TetrisItemType::Z:
		m_cube.push_back({ true, true, false });
		m_cube.push_back({ false, true, true });
		m_rows = 2;
		m_columns = 3;
		break;
	default:
		break;
	}
}
