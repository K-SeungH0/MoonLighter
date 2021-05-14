#pragma once
#include "Item.h"
enum class WEAPONTYPE
{
	BIGSWORD,
	SHORTSWORD,
	BOW,
	GLOVES,
	SPEAR,
	NONE
};

class Equipment : public Item
{
private:
	int damage;
	WEAPONTYPE type;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void ChangeType(WEAPONTYPE type);

	inline int GetDamage() { return this->damage; }
	inline WEAPONTYPE GetType() { return this->type; }

	~Equipment() override {};
};

