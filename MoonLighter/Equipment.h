#pragma once
#include "Item.h"

class Player;
enum class DIR;

enum class WEAPONTYPE
{
	BIGSWORD,
	SHORTSWORD,
	BOW,
	GLOVES,
	SPEAR,
	NONE
};
struct AttackInfo 
{
	int sizeX;
	int sizeY;
	POINTFLOAT pos;
};
class Equipment : public Item
{
private:
	int damage;
	WEAPONTYPE weaponType;
	Player* player;
	map<pair<WEAPONTYPE, DIR>, AttackInfo> attacks;
	
public:
	HRESULT Init(Player* player);
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void AttackInfoInit();
	
	void Attack();
	void ChangeType(WEAPONTYPE type);
	void ResetAttackCollider();

	void ImageLoad();

	inline int GetDamage() { return this->damage; }
	inline WEAPONTYPE GetType() { return this->weaponType; }

	~Equipment() override {};
};

