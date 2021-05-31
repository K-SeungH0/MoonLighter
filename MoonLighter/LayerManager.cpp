#include "LayerManager.h"
#include "Image.h"
#include "Camera.h"

HRESULT LayerManager::Init()
{
	vObjects.clear();
    return S_OK;
}

void LayerManager::Release()
{

}

void LayerManager::Update()
{
}

void LayerManager::Render(HDC hdc)
{
	LayerSort(0, vObjects.size()-1);

	for (auto iter = vObjects.begin(); iter != vObjects.end(); iter++)
	{
		lpCamera->CameraFrameRender(hdc, iter->first, {(LONG)iter->second.x, (LONG)iter->second.y	}, iter->first->GetCurrentFrameX(), iter->first->GetCurrentFrameY(), IMAGE_SIZE, true);
    }
}

void LayerManager::AddObject(pair<Image*, POINTFLOAT> object)
{
	vObjects.push_back(object);
}

void LayerManager::RemoveObject(pair<Image*, POINTFLOAT> object)
{
	for (auto iter = vObjects.begin(); iter != vObjects.end(); iter++)
	{
		if ((iter->second.x == object.second.x) && (iter->second.y == object.second.y))
		{
			vObjects.erase(iter);
			break;
		}
	}

}

void LayerManager::LayerSort(int start, int end)
{
	if (start >= end) return;
	
	float pivot = vObjects[(start + end) / 2].second.y;
	int left = start;
	int right = end;

	while (left <= right)
	{
		while (left <= end && vObjects[left].second.y < pivot) 
			left++;
		while (right > start && vObjects[right].second.y > pivot) 
			right--;
	
		if (left <= right)
		{
			swap(vObjects[left], vObjects[right]);
			left++;
			right--;
		}
	}
	
	LayerSort(start, right);
	LayerSort(left, end);
}