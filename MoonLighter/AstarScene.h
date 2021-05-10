#pragma once
#include "GameObject.h"
#include <vector>
#define ASTAR_TILE_SIZE 60
#define ASTAR_TILE_COUNT (ASTARSIZE_Y / ASTAR_TILE_SIZE)

class Image;

enum class ASTARTILETYPE
{
	START,
	END,
	WALL,
	NONE
};

class AstarTile : public GameObject
{
private:
	int idX, idY;
	POINT center;
	RECT rc;
	ASTARTILETYPE type;

	int costFromStart;	// G : ������ ���� ���� �������� ���
	int costToGoal;		// H : ���� ������ ������������ ���� ���
	int totalCost;		// F : G + H

	AstarTile* parentTile;	// G�� ���� �� ������ ���� ��带 ����

	bool isInOpenList;
	bool isClosed;

	COLORREF color;
	HBRUSH hBrush;
	HBRUSH hOldBrush;

	char szText[128];

	// �� ����
	int heapIndex;
public:
	HRESULT Init() override;
	HRESULT Init(int idX, int idY);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	ASTARTILETYPE GetType() { return this->type; }
	POINT GetIdXY() { return { this->idX, this->idY }; }
	int GetG() { return this->costFromStart; }
	int GetF() { return this->totalCost; }
	int GetH() { return this->costToGoal; }
	AstarTile* GetParentTile() { return this->parentTile; }
	bool GetIsInOpenList() { return this->isInOpenList; }
	bool GetIsClosed() { return this->isClosed; }
	int GetHeapIndex() { return this->heapIndex; }

	void SetG(int costFromStart) { this->costFromStart = costFromStart; }
	void SetH(int costToGoal) { this->costToGoal = costToGoal; }
	void SetF(int totalCost) { this->totalCost = totalCost; }
	void SetIsInOpenList(bool isInOpenList) { this->isInOpenList = isInOpenList; }
	void SetIsClosed(bool isClosed) { this->isClosed = isClosed; }
	void SetParentTile(AstarTile* parentTile) { this->parentTile = parentTile; }
	void SetType(ASTARTILETYPE type) { this->type = type; }
	void SetColor(COLORREF color);
	void SetHeapIndex(int heapIndex) { this->heapIndex = heapIndex; }

	~AstarTile() override {};
};
class AstarScene : public GameObject
{
private:
	AstarTile map[ASTAR_TILE_COUNT][ASTAR_TILE_COUNT];

	Image* testImage;

	AstarTile* startTile;	// ������
	AstarTile* endTile;		// �Ķ���
	AstarTile* currTile;	// (���)�ĺ� Ÿ���� �����Ҷ� ����Ÿ��

	vector<AstarTile*> openList;
	vector<AstarTile*> closeList;
	vector<AstarTile*> heap;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void FindPath();
	void AddOpenList(AstarTile* currTile);
	bool AddList(int x, int y);
	void InsertOpenlistWithHeap(AstarTile* tile);
	AstarTile* GetMinTotalCostTile();
	AstarTile* GetMinTotalCostTileWithHeap();
	void UpdateUpper(AstarTile* tile);
	void UpdateLower(AstarTile* tile);
	void Swap(AstarTile* tile1, AstarTile* tile2);

	void NextOpenList();
	void PrintPath();

	void DeleteTileInOpenList(AstarTile* tile);
	int CalcCost(int x, int y);
	int CalcHeuristic(int x, int y);
	void MarkTileToType();
	~AstarScene() override {};
};

