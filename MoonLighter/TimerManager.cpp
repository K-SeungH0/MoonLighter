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
	SetBkMode(hdc, 1);
	SetTextColor(hdc, RGB(255, 255, 255));
	if (timer)
	{
		wsprintf(szText, "FPS : %d", timer->GetFPS());
		TextOut(hdc, 20, 20, szText, strlen(szText));
	}
}

float TimerManager::GetDeltaTime()
{
	return timer->GetTimeElapsed();
}
