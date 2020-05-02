#include "TetrisItem.h"

std::unordered_map<TetrisItemType, std::unordered_map<TetrisItemRotation, TetrisItem>> TetrisItem::itemsMap;

TetrisItem& TetrisItem::GetTetrisItem(TetrisItemType type, TetrisItemRotation rotation)
{
	return itemsMap[type][rotation];
}

void TetrisItem::InitTetrisItemsMap()
{
	static bool itemsMapHasInited = false;
	if (itemsMapHasInited)
	{
		return;
	}
	std::vector<TetrisItemType> types = { I, J, L, O, S, T, Z };
	std::vector<TetrisItemRotation> rotations = { R0, R90, R180, R270 };
	for (auto& type : types)
	{
		std::unordered_map<TetrisItemRotation, TetrisItem> itemMap;
		for (auto& rotation : rotations)
		{
			itemMap.emplace(rotation, TetrisItem(type, rotation));
		}
		itemsMap.emplace(type, itemMap);
	}
	itemsMapHasInited = true;
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
	case R0:
		break;
	case R90:
		_row = m_rows - 1 - column;
		_column = row;
		break;
	case R180:
		_row = m_rows - 1 - row;
		_column = m_columns - 1 - column;
		break;
	case R270:
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
	if (m_rotation == R0 || m_rotation == R180)
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
	case I:
		m_cube.push_back({ true, true, true, true });
		m_rows = 1;
		m_columns = 4;
		break;
	case J:
		m_cube.push_back({ true, false, false });
		m_cube.push_back({ true, true, true });
		m_rows = 2;
		m_columns = 3;
		break;
	case L:
		m_cube.push_back({ false, false, true });
		m_cube.push_back({ true, true, true });
		m_rows = 2;
		m_columns = 3;
		break;
	case O:
		m_cube.push_back({ true, true });
		m_cube.push_back({ true, true });
		m_rows = 2;
		m_columns = 2;
		break;
	case S:
		m_cube.push_back({ false, true, true });
		m_cube.push_back({ true, true, false });
		m_rows = 2;
		m_columns = 3;
		break;
	case T:
		m_cube.push_back({ false, true, false });
		m_cube.push_back({ true, true, true });
		m_rows = 2;
		m_columns = 3;
		break;
	case Z:
		m_cube.push_back({ true, true, false });
		m_cube.push_back({ false, true, true });
		m_rows = 2;
		m_columns = 3;
		break;
	default:
		break;
	}
}
