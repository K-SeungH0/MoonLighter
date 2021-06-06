#include "Unit.h"
#include "Image.h"
#include "Player.h"

HRESULT Unit::Init()
{
    return S_OK;
}

void Unit::Release()
{
}

void Unit::Update()
{

}

void Unit::Render(HDC hdc)
{
    if (isDebugMode)
        Rectangle(hdc, cameraCollider.left, cameraCollider.top, cameraCollider.right, cameraCollider.bottom);
}

void Unit::Hit(Unit* attacker, Image* hitEffect)
{
    if (this == attacker) return;

    if (state != STATE::AVOID && hitTime <= 0)
    {
        //state = STATE::HIT;
        hitTime = setHitTime;
        this->hp -= attacker->GetDamage();
        
        EFFECTMANAGER->EffectRender(hitEffect, { (int)this->pos.x - lpImage->GetFrameWidth()/4 , (int)this->pos.y - lpImage->GetFrameHeight() / 4 }, (int)attacker->GetDir());
        FLOATINGFONT->DamageRender({ (int)this->pos.x, (int)this->pos.y }, attacker->GetDamage(), 0.75f);

    }
}
