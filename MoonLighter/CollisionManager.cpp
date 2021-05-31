#include "CollisionManager.h"
//#include "Object.h"
#include "Unit.h"
#include "Image.h"
bool RectInRectFloat(RECTFLOAT rc1, RECTFLOAT rc2)
{
	if (rc1.right < rc2.left || rc1.left > rc2.right
		|| rc1.top > rc2.bottom || rc1.bottom < rc2.top)
		return false;

	return true;
}

HRESULT CollisionManager::Init()
{
	return S_OK;
}

void CollisionManager::Release()
{

}

void CollisionManager::AddCollider(Object* object)
{
	vColliders.push_back(object);
}

void CollisionManager::AddPixelCollider(Image* lpImage, POINTFLOAT pos)
{
	vPixelColliders.push_back(make_pair(lpImage, pos));
}

void CollisionManager::RemoveCollider(Object* obejct)
{
	vColliders.erase(find(vColliders.begin(), vColliders.end(), obejct));
}

void CollisionManager::RemovePixelCollider()
{
    for (auto iter = vPixelColliders.begin(); iter != vPixelColliders.end();)
    {
        iter = vPixelColliders.erase(iter);
    }
}

vector<Object*> CollisionManager::CheckCollider(Object* own)
{
	vector<Object*> collidedObjects;

	for (auto iter = vColliders.begin(); iter != vColliders.end(); iter++)
	{
		if (own == *iter) continue;

		if (RectInRectFloat(own->GetCollider(), (*iter)->GetCollider()))
		{
			collidedObjects.push_back(*iter);
		}
	}
 	return collidedObjects;
}

bool CollisionManager::CheckPixelCollider(Object* own, COLORREF checkColor)
{
    COLORREF color;
    int R, G, B;
    POINT pos = { 0,0 };
    DIR dir;
    bool isHorizontal = false;

    dir = ((Unit*)own)->GetDir();


    for (auto iter = vPixelColliders.begin(); iter != vPixelColliders.end(); iter++)
    {
        switch (dir)
        {
        case DIR::LEFT:
            pos.x = own->GetCollider().left - iter->second.x;
            pos.y = own->GetCollider().top - iter->second.y;
            isHorizontal = false;
            break;
        case DIR::UP:
            pos.x = own->GetCollider().left - iter->second.x;
            pos.y = own->GetCollider().top - iter->second.y;
            isHorizontal = true;
            break;
        case DIR::RIGHT:
            pos.x = own->GetCollider().right - iter->second.x;
            pos.y = own->GetCollider().top - iter->second.y;
            isHorizontal = false;
            break;
        case DIR::DOWN:
            pos.x = own->GetCollider().right - iter->second.x;
            pos.y = own->GetCollider().bottom - iter->second.y;
            isHorizontal = true;
            break;
        }
        
        if (isHorizontal)
        {
            for (; pos.x <= own->GetCollider().right; pos.x++)
            {
                color = GetPixel(iter->first->GetMemDC(), pos.x, pos.y);

                if (checkColor == color)
                {
                    return true;
                }
            }
        }
        else
        {
            for (; pos.y <= own->GetCollider().bottom; pos.y++)
            {
                color = GetPixel(iter->first->GetMemDC(), pos.x, pos.y);

                if (checkColor == color)
                {
                    return true;
                }
            }
        }
        
    }
	return false;
}
