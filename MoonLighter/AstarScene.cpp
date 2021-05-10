#include "AstarScene.h"
#include "CommonFunction.h"
#include <math.h>
#include "Image.h"
HRESULT AstarTile::Init()
{
	return E_NOTIMPL;
}

HRESULT AstarTile::Init(int idX, int idY)
{
	this->idX = idX;
	this->idY = idY;

	center.x = idX * ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);
	center.y = idY * ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);

	rc.left = idX * ASTAR_TILE_SIZE;
	rc.right = ASTAR_TILE_SIZE + rc.left;
	rc.top = idY * ASTAR_TILE_SIZE;
	rc.bottom = ASTAR_TILE_SIZE + rc.top;

	costFromStart = 0;
	costToGoal = 0;
	totalCost = 0;

	parentTile = nullptr;

	color = RGB(100, 100, 100);
	hBrush = CreateSolidBrush(color);

	type = ASTARTILETYPE::NONE;
	isInOpenList = false;
	isClosed = false;

	return S_OK;
}

void AstarTile::Release()
{
}

void AstarTile::Update()
{
}

void AstarTile::Render(HDC hdc)
{
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	FillRect(hdc, &rc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	SelectObject(hdc, hOldBrush);

	//wsprintf(szText, "F : %d", totalCost);
	//TextOut(hdc, rc.left + 5, rc.top, szText, strlen(szText));
	//wsprintf(szText, "G : %d", costFromStart);
	//TextOut(hdc, rc.left + 5, rc.top + 20, szText, strlen(szText));
	//wsprintf(szText, "H : %d", costToGoal);
	//TextOut(hdc, rc.left - 55, rc.top + 40, szText, strlen(szText));
}

void AstarTile::SetColor(COLORREF color)
{
	this->color = color;
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(this->color);
}

HRESULT AstarScene::Init()
{
	SetClientRect(g_hWnd, ASTARSIZE_X, ASTARSIZE_Y);

	for (int i = 0; i < ASTAR_TILE_COUNT; i++)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)
		{
			map[i][j].Init(j, i);
		}
	}

	startTile = &(map[2][13]);
	startTile->SetColor(RGB(255, 0, 0));
	startTile->SetType(ASTARTILETYPE::START);

	currTile = startTile;

	endTile = &(map[13][3]);
	endTile->SetColor(RGB(0, 0, 255));
	endTile->SetType(ASTARTILETYPE::END);
	IMAGEMANAGER->AddImage("�÷��̾� ���� �̵�", L"Image/Player/Dungeon/Move/Player_Move_Front_01.png", 128, 128, 1, 1, true, RGB(128, 128, 128));

	testImage = IMAGEMANAGER->FindImage("�÷��̾� ���� �̵�");
	return S_OK;
}

void AstarScene::Release()
{

}

void AstarScene::Update()
{
	// ȭ�� ��ȯ �׽�Ʈ
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1))
	{
		SceneManager::GetInstance()->ChageScene("Battle_1");
		return;
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F2))
	{
		SceneManager::GetInstance()->ChageScene("TileMapTool", "LoadingScene");
		return;
	}

	if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
	{
		int selectX = g_ptMouse.x / ASTAR_TILE_SIZE;
		int selectY = g_ptMouse.y / ASTAR_TILE_SIZE;

		if (selectX < ASTAR_TILE_COUNT && selectX >= 0 &&
			selectY < ASTAR_TILE_COUNT && selectY >= 0 &&
			map[selectY][selectX].GetType() != ASTARTILETYPE::START &&
			map[selectY][selectX].GetType() != ASTARTILETYPE::END)
		{
			map[selectY][selectX].Init(selectX, selectY);
			map[selectY][selectX].SetColor(RGB(100, 150, 100));
			map[selectY][selectX].SetType(ASTARTILETYPE::WALL);
		}

		//wallTile.push_back(new AstarTile());
		//wallTile.back()->Init(selectX, selectY);
		//wallTile.back()->SetColor(RGB(255, 0, 255));
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown('D'))
	{
		FindPath();
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('C'))
	{
		PrintPath();
	}
}

void AstarScene::Render(HDC hdc)
{
	//for (int i = 0; i < ASTAR_TILE_COUNT; i++)
	//{
	//	for (int j = 0; j < ASTAR_TILE_COUNT; j++)
	//	{
	//		map[i][j].Render(hdc);
	//	}
	//}

	//for (auto iter = openList.begin(); iter != openList.end(); iter++)
	//{
	//	(*iter)->Render(hdc);
	//}
	
	//PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	testImage->FrameRender(hdc, WINSIZE_X / 4, WINSIZE_Y / 4, 0, 0, 2);
}


void AstarScene::FindPath()
{
	if (currTile)
	{
		// ������ �̵��� Ÿ�ϵ��� F�� ��� �ĺ��� �ִ´�.
		AddOpenList(currTile);
		//DeleteTileInOpenList(currTile);

		// �ĺ��� �� F���� ���� ���� Ÿ���� ���� currTile�� ����
		//NextOpenList();
		currTile = GetMinTotalCostTileWithHeap();
		currTile->SetColor(RGB(130, 200, 130));

		if (currTile == endTile)
			return;

		// �ݺ�
		//FindPath();

		// ���
		//PrintPath();

	}
}



void AstarScene::AddOpenList(AstarTile* currTile)
{
	//int currIdX = currTile->GetIdXY().x, currIdY = currTile->GetIdXY().y;
	//int endIdX = endTile->GetIdXY().x, endIdY = endTile->GetIdXY().y;
	//int nextIdX = 0, nextIdY = 0;
	//int max = 9999999999;
	//int cost;
	//bool _continue = false;
	//bool open = true;
	//for (int y = currIdY - 1; y <= currIdY + 1; y++)
	//{
	//	for (int x = currIdX  -1; x <= currIdX + 1; x++)
	//	{
	//		if ((x) > -1 &&	(y) > -1 &&	(x) < ASTAR_TILE_COUNT && (y) < ASTAR_TILE_COUNT)
	//		{
	//			if (&map[y][x] == currTile) continue;
	//			if (map[y][x].GetType() == ASTARTILETYPE::WALL) continue;

	//			for (auto iter = closeList.begin(); iter != closeList.end(); iter++)
	//			{
	//				if ((*iter) == &map[y][x])
	//				{
	//					_continue = true;
	//					break;
	//				}
	//			}
	//			for (auto iter = openList.begin(); iter != openList.end(); iter++)
	//			{
	//				if ((*iter) == &map[y][x])
	//				{
	//					open = false;
	//					break;
	//				}
	//				else
	//				{
	//					open = true;
	//				}
	//			}
	//			if (_continue)
	//			{
	//				_continue = false;
	//				continue;
	//			}

	//			if (y == currIdY || x == currIdX) cost = 10;
	//			else cost = 14;

	//			map[y][x].SetH(abs(10 * (endIdX - (x))) + abs(10 * (endIdY - (y))));
	//			map[y][x].SetG(sumG + cost);
	//			map[y][x].SetF();
	//			//map[y][x].SetParentTile(currTile);

	//			map[y][x].SetParentTile(this->currTile);

	//			if(open)
	//				openList.push_back(&map[y][x]);
	//			//map[y][x].SetColor(RGB(0, 255, 255));
	//		}
	//	}
	//}
	//for (auto iter = openList.begin(); iter != openList.end(); iter++)
	//{
	//	if ((*iter) == this->currTile)
	//	{
	//		openList.erase(iter);
	//		break;
	//	}
	//}

	//closeList.push_back(this->currTile);
	////this->currTile->SetColor(RGB(255, 0, 255));

	// -------------------------------------------------------------------------------------------

	// ���� �߰�
	int currIdX = currTile->GetIdXY().x;
	int currIdY = currTile->GetIdXY().y;
	bool diagonal = false;

	// �� �� �� �� 
	diagonal |= AddList(currIdX, currIdY - 1);
	diagonal |= AddList(currIdX, currIdY + 1);
	diagonal |= AddList(currIdX - 1, currIdY);
	diagonal |= AddList(currIdX + 1, currIdY);

	if (diagonal)
	{
		// �� �� �� ��
		AddList(currIdX + 1, currIdY - 1);
		AddList(currIdX - 1, currIdY - 1);
		AddList(currIdX - 1, currIdY + 1);
		AddList(currIdX + 1, currIdY + 1);
	}
	currTile->SetIsClosed(true);
}

bool AstarScene::AddList(int x, int y)
{
	int currIdX = currTile->GetIdXY().x;
	int currIdY = currTile->GetIdXY().y;

	if (x < 0 || x >= ASTAR_TILE_COUNT ||
		y < 0 || y >= ASTAR_TILE_COUNT)
		return false;

	// ���¸���Ʈ �߰� �ȵ� ����
	// 1. Ÿ���� Wall �϶�
	if (map[y][x].GetType() == ASTARTILETYPE::WALL)
		return false;

	// 2. �̹� Ȯ�ε� Ÿ���� �� (closeList)
	if (map[y][x].GetIsClosed())
		return false;

	// 3. �̹� ���¸���Ʈ�� ������
	int F, G, H;
	if (map[y][x].GetIsInOpenList())
	{
		G = map[y][x].GetG();

		if (G > currTile->GetG() + CalcCost(x, y))
		{
			G = currTile->GetG() + CalcCost(x, y);
			map[y][x].SetG(G);

			F = G + map[y][x].GetH();
			map[y][x].SetF(F);


			// parentNode�� ����
			map[y][x].SetParentTile(currTile);
		}
		return false;
	}
	else
	{
		// F, G, H ����
		G = currTile->GetG() + CalcCost(x, y);
		H = CalcHeuristic(x, y);
		F = G + H;

		map[y][x].SetG(G);
		map[y][x].SetH(H);
		map[y][x].SetF(F);

		// parentNode�� ����
		map[y][x].SetParentTile(currTile);

		// opeeList�� �߰�
		map[y][x].SetIsInOpenList(true);

		// heap �ڷᱸ���� �߰�
		InsertOpenlistWithHeap(&map[y][x]);
		map[y][x].SetColor(RGB(200, 150, 150));
		return true;
	}
}

void AstarScene::InsertOpenlistWithHeap(AstarTile* tile)
{
	heap.push_back(tile);
	tile->SetHeapIndex(heap.size() - 1);

	// �θ� Ÿ�ϰ� ���ϸ鼭 ����
	UpdateUpper(tile);
}

AstarTile* AstarScene::GetMinTotalCostTile()
{
	// TODO : Heap ������ ���� ȿ���� ����
	int minF = INT_MAX;
	AstarTile* minFTile = nullptr;
	for (int i = 0; i < openList.size(); i++)
	{
		if (minF > openList[i]->GetF())
		{
			minF = openList[i]->GetF();
			minFTile = openList[i];
		}
	}
	return minFTile;
}

AstarTile* AstarScene::GetMinTotalCostTileWithHeap()
{
	if (heap.empty()) return nullptr;

	AstarTile* tile = heap[0];

	heap[0] = heap.back();
	heap[0]->SetHeapIndex(0);
	heap.pop_back();

	// �ڽİ� ���ϸ鼭 ����
	UpdateLower(heap[0]);

	return tile;
}

void AstarScene::UpdateUpper(AstarTile* tile)
{
	if (tile->GetHeapIndex() == 0)
		return;

	int parentIndex = (tile->GetHeapIndex() - 1) / 2;

	AstarTile* parentTile = heap[parentIndex];

	if (parentTile->GetF() > tile->GetF())
	{
		Swap(parentTile, tile);
		UpdateUpper(tile);
	}
}

void AstarScene::UpdateLower(AstarTile* tile)
{
	int lChildIndex = tile->GetHeapIndex() * 2 + 1;

	if (lChildIndex >= heap.size())
		return;

	AstarTile* lChild = heap[lChildIndex];	// �θ��� �ε��� * 2
	AstarTile* minChild = lChild;

	int rChildIndex = tile->GetHeapIndex() * 2 + 2;
	if (rChildIndex < heap.size())
	{
		AstarTile* rChild = heap[rChildIndex];	// �θ��� �ε��� * 2 + 1
		// ��
		if (lChild->GetF() > rChild->GetF())
		{
			minChild = rChild;
		}
	}

	if (tile->GetF() > minChild->GetF())
	{
		Swap(tile, minChild);
		UpdateLower(tile);
	}
}

void AstarScene::Swap(AstarTile* tile1, AstarTile* tile2)
{
	heap[tile1->GetHeapIndex()] = tile2;
	heap[tile2->GetHeapIndex()] = tile1;

	int temp = tile1->GetHeapIndex();
	tile1->SetHeapIndex(tile2->GetHeapIndex());
	tile2->SetHeapIndex(temp);
}

void AstarScene::NextOpenList()
{
	int min = INT_MAX;
	int nextX = 0, nextY = 0;

	for (auto iter = openList.begin(); iter != openList.end(); iter++)
	{
		if (min > (*iter)->GetF())
		{
			min = (*iter)->GetF();
			nextX = (*iter)->GetIdXY().x;
			nextY = (*iter)->GetIdXY().y;
		}
	}
	currTile = &map[nextY][nextX];
	//this->currTile->SetColor(RGB(0, 150, 0));
}

void AstarScene::PrintPath()
{
	AstarTile* targetTile = endTile;

	while (targetTile != startTile)
	{
		targetTile = targetTile->GetParentTile();
		targetTile->SetColor(RGB(255, 0, 255));
	}
}

void AstarScene::DeleteTileInOpenList(AstarTile* tile)
{
	// TODO : Heap �������� ����
	for (vector<AstarTile*>::iterator iter = openList.begin(); iter != openList.end(); iter++)
	{
		if ((*iter) == tile)
		{
			openList.erase(iter);
			break;
		}
	}
}

int AstarScene::CalcCost(int x, int y)
{
	return (y == currTile->GetIdXY().y || x == currTile->GetIdXY().x) ? 10 : 14;
}

int AstarScene::CalcHeuristic(int x, int y)
{
	return 10 * (abs(endTile->GetIdXY().x - x) + abs(endTile->GetIdXY().y - y));
}

void AstarScene::MarkTileToType()
{
	AstarTile* parentTile = endTile;
}
