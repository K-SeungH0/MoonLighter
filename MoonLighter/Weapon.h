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

class Weapon : public Item
{
private:
	Image* lpEffectImage;
	int damage;
	WEAPONTYPE weaponType;
	Player* player;
	map<pair<WEAPONTYPE, DIR>, AttackInfo> attacks;
	
	bool imageLoaded = false;
public:
	HRESULT Init(GameData::ItemData itemData, ItemManager* lpItemManager);
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void AttackInfoInit();
	
	void Attack();
	void ChangeType();
	void ResetAttackCollider();

	void ImageLoad();

	inline int GetDamage() { return this->damage; }
	inline WEAPONTYPE GetType() { return this->weaponType; }

	~Weapon() override {};
};

