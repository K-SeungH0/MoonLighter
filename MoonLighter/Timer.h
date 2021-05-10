#pragma once
#include "MoonLighter.h"

class Timer
{
private:
	bool isHardware;			// ���� Ÿ�̸Ӹ� �� �� �ִ��� ����
	float timeScale;			// ��� �������� �ʴ� �������� ������ �������� �ð����� ȯ��
	float timeElapsed;			// ������ �ð��� ���� �ð��� �����
	__int64 currentTime;		// ���� �ð� (���� Ÿ�̸� ���� ��)
	__int64 lastTime;			// ���� �ð� (���� Ÿ�̸� ���� ��)
	__int64 periodFrequency;	// ���� Ÿ�̸� ���ļ� (�ʴ� ������)

	float fpsTimeElapsed;		// ������ ��� �ð� (1�� Ȯ��)
	unsigned long fpsFrameCount;// �ʴ� �����Ӽ�
	unsigned long FPS;
public:
	HRESULT Init();
	void Tick();

	inline unsigned long GetFPS() { return this->FPS; }
	inline float GetTimeElapsed() { return this->timeElapsed; }
	inline float GetFpsFrameCount() { return this->fpsFrameCount; }
};

