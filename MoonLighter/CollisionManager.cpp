#include "CollisionManager.h"
#include "Object.h"

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

void CollisionManager::RemoveCollider(Object* obejct)
{
	vColliders.erase(find(vColliders.begin(), vColliders.end(), obejct));
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
