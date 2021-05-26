#include "TimerManager.h"
#include "Timer.h"

HRESULT TimerManager::Init()
{
	timer = new Timer();
	timer->Init();
	return S_OK;
}

void TimerManager::Release()
{
	SAFE_DELETE(timer);
}

void TimerManager::Update()
{
	if (timer)
		timer->Tick();
}

void TimerManager::Render(HDC hdc)
{
	if (timer)
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		wsprintf(szText, "FPS : %d", timer->GetFPS());
		TextOut(hdc, 5, 5, szText, strlen(szText));
	}
}

float TimerManager::GetDeltaTime()
{
	return timer->GetTimeElapsed();
}
