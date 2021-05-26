#pragma once
#include "GameObject.h"
// 1200 * 640

class Image;
class Button;

enum class SELECTSCENE
{
	TOWN,
	DUNGEON,
	NONE
};
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

	Button* townSelectButton;
	Button* dungeonSelectButton;

	int selectStage;
	char szText[128];

	POINT cameraPos;
	SELECTSCENE currentScene;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void StageSelect(int num);
	void Save(int stageNum);
	void Load(int stageNum);
	void SceneSelect(int num);

	void TileSelect();
	void ImageLoad();
	virtual ~TileMapTool() {};
};