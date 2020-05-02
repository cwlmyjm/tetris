#pragma once
#include <vector>
#include <array>

using namespace std;

enum class TetrisItemType
{
	I = 'I',
	J = 'J',
	L = 'L',
	O = 'O',
	S = 'S',
	T = 'T',
	Z = 'Z',
};


enum class TetrisItemRotation
{
	R0 = 0,
	R90 = 90,
	R180 = 180,
	R270 = 270,
};

class TetrisItem
{
public:
	static std::array<TetrisItem, 28> itemsMap;
	static TetrisItem& GetTetrisItem(const TetrisItemType& type, const TetrisItemRotation& rotation);
	static void InitTetrisItemsMap();

private:
	static int TetrisItemType2Int(const TetrisItemType& type);
	static int TetrisItemRotation2Int(const TetrisItemRotation& rotation);
	static int TetrisItemTypeRotation2Int(const TetrisItemType& type, const TetrisItemRotation& rotation);

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

