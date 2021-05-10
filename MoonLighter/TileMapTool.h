#pragma once
#include "GameObject.h"

#define SAMPLE_TILE_X	6
#define SAMPLE_TILE_Y	1
#define TILESIZE		24

#define TILE_X			26 
#define TILE_Y			26

class Image;
class Button;
class TileMapTool : public GameObject
{
private:
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];

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

