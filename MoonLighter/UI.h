#pragma once
#include "GameObject.h"

class Image;

class UI : public GameObject
{
protected:
	Image* lpImage;
	POINT pos;
	int frameX;
	int frameY;
	int cutX;
	int cutY;

public:
	HRESULT Init() override;
	HRESULT Init(Image* lpImage, POINT pos, int frameX = 0, int frameY = 0, int cutX = 0, int cutY = 0);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	inline int GetCutX() { return this->cutX; }
	inline int GetCutY() { return this->cutY; }
	inline int GetFrameX() { return this->frameX; }
	inline int GetFrameY() { return this->frameY; }

	inline void SetCutX(int cutX) { this->cutX = cutX; }
	inline void SetCutY(int cutY) { this->cutY = cutY; }
	inline void SetFrameX(int frameX) { this->frameX = frameX; }
	inline void SetFrameY(int frameY) { this->frameY = frameY; }
	inline void SetPos(POINT pos) { this->pos = pos; }

	virtual ~UI() {};
};

