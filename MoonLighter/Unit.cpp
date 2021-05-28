#include "Unit.h"
#include "Image.h"

HRESULT Unit::Init()
{
    return S_OK;
}

void Unit::Release()
 {
    delete this; 
}

void Unit::Update()
{

}

void Unit::Render(HDC hdc)
{
    if (isDebugMode)
        Rectangle(hdc, cameraCollider.left, cameraCollider.top, cameraCollider.right, cameraCollider.bottom);
}

void Unit::Hit()
{
    state = STATE::HIT;
    
}
