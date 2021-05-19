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
        Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);
}

void Unit::Hit()
{

}
