#pragma once
#include "GameObject.h"
#include "TileMapTool.h"

enum class BUTTONSTATE
{
	NONE,
	DOWN,
	UP
};
class Image;
class Button : public GameObject
{
private:
	BUTTONSTATE state;
	Image* image;
	RECT rc;
	POINT pos;

	TileMapTool* tileMap;
    void(TileMapTool::*Click)(int);

	int index;
	string name;
	//string _name;
public:
	HRESULT Init(string name, POINT pos);
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void SetTileMap(TileMapTool* tileMap) { this->tileMap = tileMap; }
	void SetClick(void(TileMapTool::* Click)(int), int index) { this->Click = Click; this->index = index; }
	virtual ~Button() {};
};

