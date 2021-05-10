#include "Timer.h"

HRESULT Timer::Init()
{
	isHardware = false;
	timeScale = 0.0f;
	timeElapsed = 0.0f;
	currentTime = 0.0;
	lastTime = 0.0;
	periodFrequency = 0.0;
	fpsTimeElapsed = 0.0f;
	fpsFrameCount = 0;

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;
	}
	return S_OK;
}

void Timer::Tick()
{
	// 현재 진동수 or 현재 시간을 구해서 경과 시간을 계산
	if (isHardware)
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	else
		currentTime = timeGetTime();

	timeElapsed = (currentTime - lastTime) * timeScale;
	// 프레임 계산
	fpsTimeElapsed += timeElapsed;
	fpsFrameCount++;
	if (fpsTimeElapsed >= 1.0f)
	{
		FPS = fpsFrameCount;
		fpsFrameCount = 0.0f;
		fpsTimeElapsed -= 1.0f;
	}
	lastTime = currentTime;
}
