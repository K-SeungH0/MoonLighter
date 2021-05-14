#include "Unit.h"
#include "Image.h"

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
        Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
}

void Unit::Hit()
{

}
