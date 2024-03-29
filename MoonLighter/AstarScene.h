#pragma once
#include "GameObject.h"
#include <vector>
#define ASTAR_TILE_SIZE 64
//#define ASTAR_TILE_COUNT (ASTARSIZE_Y / ASTAR_TILE_SIZE)

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
	POINT pos;
	RECT rc;
	ASTARTILETYPE type;

	int costFromStart;	// G : 시작점 부터 현재 노드까지의 비용
	int costToGoal;		// H : 현재 노드부터 목적지꺼지의 예상 비용
	int totalCost;		// F : G + H

	AstarTile* parentTile;	// G가 갱신 될 때마다 이전 노드를 갱신

	bool isInOpenList;
	bool isClosed;

	COLORREF color;
	HBRUSH hBrush;
	HBRUSH hOldBrush;

	char szText[128];

	// 힙 관련
	int heapIndex;
public:
	HRESULT Init() override;
	HRESULT Init(int idX, int idY);
	HRESULT Init(int idX, int idY, TILE_INFO tile);
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
	POINT GetPos() { return this->pos; }


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
	AstarTile map[DUNGEON_TILE_Y][DUNGEON_TILE_X];

	AstarTile* startTile;	// 빨간색
	AstarTile* endTile;		// 파란색
	AstarTile* currTile;	// (녹색)후보 타일을 선정할때 기준타일

	vector<AstarTile*> openList;
	vector<AstarTile*> closeList;
	vector<AstarTile*> heap;
	vector<POINT> result;
public:
	HRESULT Init() override;
	HRESULT Init(TILE_INFO* tile);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void FindPath();
	//vector<> FindPath();
	void AddOpenList(AstarTile* currTile);
	void AddList(int x, int y);
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

	vector<POINT> Result();
	void ResetInfo();

	inline void SetEndTile(int x, int y) { this->endTile = &(map[y][x]); this->endTile->SetType(ASTARTILETYPE::END); }
	inline void SetStartTile(int x, int y) { this->startTile = &(map[y][x]); this->startTile->SetType(ASTARTILETYPE::START); this->currTile = startTile; }

	~AstarScene() override {};
};

