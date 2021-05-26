#include "EffectManager.h"
#include "Image.h"

HRESULT EffectManager::Init()
{
    return S_OK;
}

void EffectManager::Release()
{

}

void EffectManager::Update()
{
    for (auto iter = vEffectInfo.begin(); iter != vEffectInfo.end();)
    {
        iter->timer += DELTATIME; //TimerManager::GetInstance()->GetDeltaTime();

        if (iter->timer >= 0.1f)
        {
            iter->timer -= 0.1f;

            if (++(iter->frame) > 2)
                iter = vEffectInfo.erase(iter);
            else
                iter++;
        }
        else
            iter++;
    }
}

void EffectManager::Render(HDC hdc)
{
    for (auto iter = vEffectInfo.begin(); iter != vEffectInfo.end(); iter++)
    {
        iter->lpImage->FrameRender(hdc, iter->pos.x, iter->pos.y, iter->frame, iter->dir, 1.5f);
    }
}

void EffectManager::EffectRender(Image* lpImage, POINT pos, int dir)
{
    EffectInfo effectInfo;
    effectInfo.lpImage = lpImage;
    effectInfo.pos = pos;
    effectInfo.dir = dir;
    effectInfo.frame = 0;
    effectInfo.timer = 0;

    vEffectInfo.push_back(effectInfo);
}
