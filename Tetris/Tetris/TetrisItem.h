#pragma once
#include <vector>
#include <unordered_map>

using namespace std;

enum TetrisItemType
{
	I = 'I',
	J = 'J',
	L = 'L',
	O = 'O',
	S = 'S',
	T = 'T',
	Z = 'Z',
};

enum TetrisItemRotation
{
	R0 = 0,
	R90 = 90,
	R180 = 180,
	R270 = 270,
};

class TetrisItem
{
public:
	static std::unordered_map<TetrisItemType, std::unordered_map<TetrisItemRotation, TetrisItem>> itemsMap;
	static TetrisItem& GetTetrisItem(TetrisItemType type, TetrisItemRotation rotation);
	static void InitTetrisItemsMap();

public:
	TetrisItem() = default;
	TetrisItem(TetrisItemType type, TetrisItemRotation rotation);
	TetrisItem(const TetrisItem& other);
	~TetrisItem();

public:
	bool GetValue(int row, int column);
	pair<int, int> GetRect();

private:
	void Init();

private:
	TetrisItemType m_type;
	TetrisItemRotation m_rotation;
	vector<vector<bool>> m_cube;
	int m_rows = 0;
	int m_columns = 0;

};

