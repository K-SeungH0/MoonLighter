#include "Projectile.h"
#include "Image.h"
#include "Camera.h"

HRESULT Projectile::Init()
{
    moveSpeed = 350;
    isMove = false;
	return S_OK;
}

void Projectile::Release()
{

}

void Projectile::Update()
{
    if(isMove)
        Move();
}

void Projectile::Render(HDC hdc)
{
    if(isMove)
        lpCamera->CameraFrameRender(hdc, lpImage, { (LONG)pos.x, (LONG)pos.y }, 0, (int)dir, IMAGE_SIZE, true);

    if (isDebugMode)
        Rectangle(hdc, (int)collider.left, (int)collider.top, (int)collider.bottom, (int)collider.right);

    Rectangle(hdc, 212, 522, 244, 554);
}

void Projectile::Move()
{
    SetCollider();
    
    switch (dir)
    {
    case DIR::LEFT:
        collider.left -= moveSpeed * DELTATIME;

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
        {
            if (collider.left > 0)
                pos.x -= moveSpeed * DELTATIME;
            else
                this->isMove = false;
        }
        break;
    case DIR::UP:
        collider.top -= moveSpeed * DELTATIME;

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
        {
            if (collider.top > 0 )
                pos.y -= moveSpeed * DELTATIME;
            else
                this->isMove = false;
        }
        break;
    case DIR::RIGHT:
        collider.right += moveSpeed * DELTATIME;

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
        {
            if (collider.right < moveArea.x)
                pos.x += moveSpeed  * DELTATIME;    
            else
                this->isMove = false;
        }
        break;
    case DIR::DOWN:
        collider.bottom += moveSpeed * DELTATIME;

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
        {
            if (collider.bottom < moveArea.y)
                pos.y += moveSpeed * DELTATIME;
            else
                this->isMove = false;
        }
        break;
    }

    SetCollider();
}

void Projectile::Shoot(DIR dir, POINTFLOAT pos)
{
    this->dir = dir;
    this->isMove = true;
    this->pos = pos;
    SetCollider();
}

void Projectile::SetCollider()
{
    cameraCollider.left = pos.x - lpImage->GetFrameWidth() - lpCamera->GetCameraPos().x;
    collider.left = pos.x - lpImage->GetFrameWidth()/2;
    cameraCollider.top = pos.y - lpCamera->GetCameraPos().y;
    collider.top = pos.y - lpImage->GetFrameHeight()/2;
    cameraCollider.right = pos.x + lpImage->GetFrameWidth() - lpCamera->GetCameraPos().x;
    collider.right = pos.x + lpImage->GetFrameWidth()/2;
    cameraCollider.bottom = pos.y + lpImage->GetFrameHeight() - lpCamera->GetCameraPos().y;
    collider.bottom = pos.y + lpImage->GetFrameHeight()/2;
}
