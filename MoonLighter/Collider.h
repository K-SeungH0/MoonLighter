#pragma once
#include <Windows.h>

class GameObject;

class Collider
{
private:
	POINTFLOAT pos;
	RECT collider;
	GameObject* object;
};

