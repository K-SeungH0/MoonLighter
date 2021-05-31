#pragma once
#include "GameObject.h"
// 1200 * 640

class Image;
class Button;
class Camera;

struct ObjectTileInfo
{
	Image* lpSelectTile;
	RECT rcTile;
};
class TileMapTool : public GameObject
{
public:
	enum class TILESCENE
	{
		TOWN,
		DUNGEON,
		EXIT,
		NONE
	};
private:
	Image* lpBackGroundTile;
	Image* lpTownTileSetImage;
	Image* lpDunGeonTileSetImage;
	TILE_INFO selectTileInfo;
	Image* lpSelectTile;

	TILE_INFO dunGeonTileSetInfo[DUNGEON_TILE_SET_X * DUNGEON_TILE_SET_Y];
	TILE_INFO townTileSetInfo[TOWN_TILE_SET_X * TOWN_TILE_SET_Y];
	static TILE_INFO dungeonTileInfo[DUNGEON_TILE_X * DUNGEON_TILE_Y];
	static TILE_INFO townTileInfo[TOWN_TILE_X * TOWN_TILE_Y];

	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;

	POINT selectedFrame;

	int selectedFrameX;
	int selectedFrameY;

	RECT rcTownMain;
	RECT rcDungeonMain;
	
	RECT rcDungeonTileSet;
	RECT rcTownTileSet;

	// UI Button
	Button* saveButton;
	Button* loadButton;
	Button* leftButton;
	Button* rightButton;

	Button* townSelectButton;
	Button* dungeonSelectButton;
	Button* exitButton;
	int selectStage;
	char szText[128];

	TILESCENE currentScene;
	Camera* lpCamera;

	float timer;

	int selectPosX;
	int selectPosY;
	bool overTile;
	bool overlapColliderTile;
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
	ObjectTileInfo GetObjectInfo(int x, int y);
	void ImageLoad();
	virtual ~TileMapTool() {};
};