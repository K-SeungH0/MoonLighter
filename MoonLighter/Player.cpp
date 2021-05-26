#include "Player.h"
#include "Image.h"
#include "Weapon.h"
#include "CollisionManager.h"
#include "Inventory.h"

HRESULT Player::Init()
{
    ImageLoad();
    lpImage = IMAGEMANAGER->FindImage("PlayerState");
    
    moveSpeed = 250;
    armor = 10;
    maxHp = 100;
    hp = maxHp;

    additionalHp = 0;
    additionalMoveSpeed = 0;
    additionalArmor = 0;
    
    gold = 123456789;

    imageFrame = 0;
    stateFrame = 0;
    maxFrame = 0;

    frameTimer = 0;
    comboStack = 0;
    
    pos = { WINSIZE_X / 2 , WINSIZE_Y / 2 };
    
    isAction = false;
    isCombo = false;
    isEquipMainWeapon = true;

    SetHitBox();

    lpCurrentWeapon = new Weapon();
    ChangeWeapon(nullptr);

    lpPotion = nullptr;

    objectType = OBJECTTYPE::UNIT;
    COLLIDERMANAGER->AddCollider(this);
    return S_OK;
}

void Player::Release()
{
    delete this;
}

void Player::Update()
{
    if (KEYMANAGER->IsOnceKeyDown('0'))
        Die();
    
    if (KEYMANAGER->IsOnceKeyDown('E'))
    {
        if (lpPotion && hp < maxHp + additionalHp)
        {
            hp += lpPotion->GetHp();
            if (hp >= maxHp + additionalHp)
                hp = maxHp + additionalHp;

            lpPotion->Use();
        }
    }


    if (state != STATE::AVOID && KEYMANAGER->IsOnceKeyDown('A'))
        Attack();

    if (KEYMANAGER->IsOnceKeyDown('D'))
        this->hp--;

    if (!isAction)
    {
        //if (KEYMANAGER->IsOnceKeyDown('1'))
        //    weapon->ChangeType(WEAPONTYPE::BIGSWORD);
        //else if (KEYMANAGER->IsOnceKeyDown('2'))
        //    weapon->ChangeType(WEAPONTYPE::SHORTSWORD);
        //else if (KEYMANAGER->IsOnceKeyDown('3'))
        //    weapon->ChangeType(WEAPONTYPE::BOW);
        //else if (KEYMANAGER->IsOnceKeyDown('4'))
        //    weapon->ChangeType(WEAPONTYPE::SPEAR);
        //else if (KEYMANAGER->IsOnceKeyDown('5'))
        //    weapon->ChangeType(WEAPONTYPE::GLOVES);
        
        state = STATE::IDLE;
        stateFrame = 8;
        stateFrame += (int)dir;
        maxFrame = 10;

        if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))          FrameReset();
        else if (KEYMANAGER->IsStayKeyDown(VK_LEFT))     Move(DIR::LEFT);

        else if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))    FrameReset();
        else if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))    Move(DIR::RIGHT);

        if (KEYMANAGER->IsOnceKeyDown(VK_UP))            FrameReset();
        else if (KEYMANAGER->IsStayKeyDown(VK_UP))       Move(DIR::UP);

        else if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))     FrameReset();
        else if (KEYMANAGER->IsStayKeyDown(VK_DOWN))     Move(DIR::DOWN);

        if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
        {
            FrameReset();
            Avoid();
        }
    }
    if(state == STATE::AVOID)
        Move(dir);

    if (state == STATE::ATTACK)
    {
        for (int i = 0; i < attackFrame.size(); i++)
        {
            if (imageFrame == attackFrame[i])
            {
                lpCurrentWeapon->Attack();
                break;
            }
            else
                lpCurrentWeapon->ResetAttackCollider();
        }
    }

    frameTimer += DELTATIME;
    
    if (frameTimer > 0.1f)
    {
        frameTimer -= 0.1f;

        // TODO : 죽었을때 상황 추가해야함
        if (state == STATE::DIE)
        {
            if (++imageFrame >= maxFrame)
            {
                imageFrame = maxFrame - 1;
            }
        }
        else if (isAction)
        {
            if (++imageFrame >= maxFrame)
            {
                isAction = false;
                moveSpeed = 250;
                lpImage = IMAGEMANAGER->FindImage("PlayerState");
                comboStack = 0;
                FrameReset();
            }
        }
        else
            (++imageFrame) %= maxFrame;
    }
    
    //if (!isAction)
    //    SetHitBox();

}

void Player::Render(HDC hdc)
{
    Unit::Render(hdc);

    lpImage->FrameRender(hdc, pos.x, pos.y, imageFrame, stateFrame, IMAGE_SIZE, true);

    if (state == STATE::ATTACK)
        lpCurrentWeapon->Render(hdc);
}

void Player::Avoid()
{
    isAction = true;
    state = STATE::AVOID;

    moveSpeed = 375;
    stateFrame = 4;
    stateFrame += (int)dir;
    maxFrame = 8;
    //collider = { 0,0,0,0 };
}

void Player::Move(DIR dir)
{
    this->dir = dir;

    if (!isAction)
    {
        state = STATE::MOVING;
        stateFrame = 0;
        stateFrame += (int)dir;
        maxFrame = 8;
    }
    
    switch (this->dir)
    {
    case DIR::LEFT:
        collider.left -= (moveSpeed + additionalMoveSpeed) * DELTATIME;
        CheckItem();

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
        {
            pos.x -= (moveSpeed + additionalMoveSpeed) * DELTATIME;
        }
        break;
    case DIR::UP:
        collider.top -= (moveSpeed + additionalMoveSpeed) * DELTATIME;
        CheckItem();

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
            pos.y -= (moveSpeed + additionalMoveSpeed) * DELTATIME;
        break;
    case DIR::RIGHT:
        collider.right += (moveSpeed + additionalMoveSpeed) * DELTATIME;
        CheckItem();

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
            pos.x += (moveSpeed + additionalMoveSpeed) * DELTATIME;
        break;
    case DIR::DOWN:
        collider.bottom += (moveSpeed + additionalMoveSpeed) * DELTATIME;
        CheckItem();

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
            pos.y += (moveSpeed + additionalMoveSpeed) * DELTATIME;
        break;
    }

    SetHitBox();
}

void Player::Die()
{
    FrameReset();
    isAction = true;
    state = STATE::DIE;
    stateFrame = 12;
}

void Player::Attack()
{
    if (comboStack == 0)
    {
        preFrame = 0;
        maxFrame = 0;
        state = STATE::ATTACK;
        stateFrame = (int)dir;
        isAction = true;
        comboStack = 1;
        FrameReset();
    }

    switch (lpCurrentWeapon->GetType())
    {
        case WEAPONTYPE::BIGSWORD:
            NextCombo(11, 22, 40);
            AddAttackFrame({ 6,17,28 });
            lpImage = IMAGEMANAGER->FindImage("BigSwordMotion");
            break;
        case WEAPONTYPE::SHORTSWORD:
        case WEAPONTYPE::NONE:
            NextCombo(5, 9, 18);
            AddAttackFrame({ 2,6,10 });
            lpImage = IMAGEMANAGER->FindImage("ShortSwordMotion");
            break;
        case WEAPONTYPE::GLOVES:
            NextCombo(5, 10, 20);
            AddAttackFrame({ 3,7,12,14 });
            lpImage = IMAGEMANAGER->FindImage("GlovesMotion");
            break;
        case WEAPONTYPE::SPEAR:
            NextCombo(6, 14, 23);
            AddAttackFrame({ 2,9,16 });
            lpImage = IMAGEMANAGER->FindImage("SpearMotion");
            break;
        case WEAPONTYPE::BOW:
            maxFrame = 7;
            lpImage = IMAGEMANAGER->FindImage("BowMotion");
            break;
    }
}

void Player::SpecialAttack()
{
    isAction = true;

    switch (lpCurrentWeapon->GetType())
    {
    case WEAPONTYPE::BIGSWORD:
        state = STATE::CHARGING;
        break;
    case WEAPONTYPE::SHORTSWORD:
        state = STATE::DEFENDING;
        break;
    case WEAPONTYPE::GLOVES:
        state = STATE::CHARGING;
        break;
    case WEAPONTYPE::SPEAR:
        state = STATE::CHARGING;
        break;
    }
}

void Player::SetHitBox()
{
    collider.left = pos.x - lpImage->GetFrameWidth() / 3;
    collider.top = pos.y;
    collider.right = pos.x + lpImage->GetFrameWidth() / 3;
    collider.bottom = pos.y + lpImage->GetFrameHeight() / 2;
}

void Player::NextCombo(int first, int second, int third)
{
    if (imageFrame >= (preFrame / 2 + maxFrame / 2))
    {
        switch (comboStack)
        {
        case 1:
            maxFrame = first;
            break;
        case 2:
            preFrame = maxFrame;
            maxFrame = second;
            break;
        case 3:
            preFrame = maxFrame;
            maxFrame = third;
            break;
        }
        comboStack++;
    }
}

void Player::AddAttackFrame(vector<int> frame)
{
    attackFrame.clear();

    attackFrame = frame;
}

void Player::ChangeWeapon(Item* weapon)
{
    if (weapon)
    {
        this->lpCurrentWeapon->Init(weapon->GetItemData(), weapon->GetItemManager());
        additionalMoveSpeed = weapon->GetSpeed();
        this->damage = this->lpCurrentWeapon->GetDamage();
    }
    else
    {
        this->lpCurrentWeapon->Init();
        additionalMoveSpeed = 0;
        this->damage = this->lpCurrentWeapon->GetDamage();
    }
}

void Player::EquipFromInventory(SLOTTYPE slotType, Item* equipment)
{
    switch (slotType)
    {
    case SLOTTYPE::INVEN:
        break;
    case SLOTTYPE::MAINWEAPON:
        lpMainWeapon = equipment;
        if(isEquipMainWeapon)
            ChangeWeapon(lpMainWeapon);
        break;
    case SLOTTYPE::SUBWEAPON:
        lpSubWeapon = equipment;
        if (!isEquipMainWeapon)
            ChangeWeapon(lpSubWeapon);
        break;
    case SLOTTYPE::HELMET:
        if (equipment)
            additionalHp = equipment->GetHp();
        else
        {
            additionalHp = 0;
            if (hp > maxHp + additionalHp)
                hp = maxHp + additionalHp;
        }
        break;
    case SLOTTYPE::CHEST:
        if (equipment)
            additionalArmor = equipment->GetArmor();
        else
            additionalArmor = 0;
        break;
    case SLOTTYPE::SHOES:
        if (equipment)
            additionalMoveSpeed = equipment->GetSpeed();
        else
            additionalMoveSpeed = 0;
        break;
    case SLOTTYPE::POTION:
        lpPotion = equipment;
        break;
    case SLOTTYPE::NONE:
        break;
    }
}

void Player::SwapWeapon()
{
    if (isEquipMainWeapon)
    {
        ChangeWeapon(lpSubWeapon);
        isEquipMainWeapon = !isEquipMainWeapon;
    }
    else
    {
        ChangeWeapon(lpMainWeapon);
        isEquipMainWeapon = !isEquipMainWeapon;
    }
}

void Player::CheckItem()
{
    auto items = COLLIDERMANAGER->CheckCollider(this);

    for (auto iter = items.begin(); iter != items.end(); iter++) 
    {
        if((*iter)->GetObjectType() == OBJECTTYPE::ITEM)
            ((Item*)*iter)->PickUp();
    }
}

void Player::ImageLoad()
{

    IMAGEMANAGER->AddImage("PlayerState", L"Image/Player/PlayerState.png",10, 13);

    IMAGEMANAGER->AddImage("BigSwordMotion", L"Image/Player/Weapon/BigSwordMotion.png", 40, 4);
    IMAGEMANAGER->AddImage("ShortSwordMotion", L"Image/Player/Weapon/ShortSwordMotion.png", 18, 4);
    IMAGEMANAGER->AddImage("GlovesMotion", L"Image/Player/Weapon/GlovesMotion.png", 20, 4);
    IMAGEMANAGER->AddImage("SpearMotion", L"Image/Player/Weapon/SpearMotion.png", 23, 4);
    IMAGEMANAGER->AddImage("BowMotion", L"Image/Player/Weapon/BowMotion.png", 7, 4);
}

void Player::FrameReset()
{
    frameTimer = 0;
    imageFrame = 0;
}

Image* Player::GetCurrentWeaponImage()
{
    return this->lpCurrentWeapon->GetItemData().lpItemImage;
}

Image* Player::GetPotionImage()
{
    if (lpPotion)
        return this->lpPotion->GetItemData().lpItemImage;
    else
        return nullptr;
}

int Player::GetPotionCount()
{
    if (lpPotion)
        return this->lpPotion->GetItemData().count;
    else
        return 0;
}
