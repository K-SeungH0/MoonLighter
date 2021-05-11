#pragma once
#include "GameObject.h"

class Image;
class Button;
class TileMapTool : public GameObject
{
private:
	Image* backGroundTile;

	Image* tileSetImage;
	TILE_INFO tileSetInfo[TILE_SET_X * TILE_SET_Y];

	static TILE_INFO tileInfo[TILE_X * TILE_Y];

	POINT ptSelected[2];
	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;
	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;

	int selectedFrameX;
	int selectedFrameY;

	RECT rcMain;
	RECT rcSample;

	// UI Button
	Button* saveButton;
	Button* loadButton;
	Button* leftButton;
	Button* rightButton;
	static int selectStage;
	char szText[20];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void StageSelect(int num);
	static void Save(int stageNum);
	static void Load(int stageNum);

	void TileSelect();

	virtual ~TileMapTool() {};
};

