#pragma once
#include "GameObject.h"
// 1200 * 640

class Image;
class Button;
class TileMapTool : public GameObject
{
private:
	Image* lpBackGroundTile;
	Image* lpTileSetImage;

	TILE_INFO tileSetInfo[TILE_SET_X * TILE_SET_Y];
	static TILE_INFO tileInfo[TILE_X * TILE_Y];

	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;

	POINT selectedFrame;

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
	char szText[128];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void StageSelect(int num);
	static void Save(int stageNum);
	static void Load(int stageNum);

	void TileSelect();
	void ImageLoad();
	virtual ~TileMapTool() {};
};

