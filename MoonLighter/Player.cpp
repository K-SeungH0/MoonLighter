#include "Player.h"
#include "Image.h"
#include "Equipment.h"
#include "CollisionManager.h"

HRESULT Player::Init()
{
    ImageLoad();
    lpImage = IMAGEMANAGER->FindImage("PlayerState");
    
    moveSpeed = 250;
    
    imageFrame = 0;
    stateFrame = 0;
    maxFrame = 0;

    frameTimer = 0;
    comboStack = 0;
    
    pos = { WINSIZE_X / 2 , WINSIZE_Y - 100 };
    
    isAction = false;
    isCombo = false;

    SetHitBox();
    weapon = new Equipment();
    weapon->Init(this);

    type = OBJECTTYPE::DYNAMIC;
    COLLIDERMANAGER->AddCollider(this);

    return S_OK;
}

void Player::Release()
{
    weapon->Release();
}

void Player::Update()
{
    if (KEYMANAGER->IsOnceKeyDown('0'))
        Die();
    
    if (state != STATE::AVOID && KEYMANAGER->IsOnceKeyDown('A'))
        Attack();

    if (!isAction)
    {
        if (KEYMANAGER->IsOnceKeyDown('1'))
            weapon->ChangeType(WEAPONTYPE::BIGSWORD);
        else if (KEYMANAGER->IsOnceKeyDown('2'))
            weapon->ChangeType(WEAPONTYPE::SHORTSWORD);
        else if (KEYMANAGER->IsOnceKeyDown('3'))
            weapon->ChangeType(WEAPONTYPE::BOW);
        else if (KEYMANAGER->IsOnceKeyDown('4'))
            weapon->ChangeType(WEAPONTYPE::SPEAR);
        else if (KEYMANAGER->IsOnceKeyDown('5'))
            weapon->ChangeType(WEAPONTYPE::GLOVES);
        
        state = STATE::IDLE;
        stateFrame = 8;
        stateFrame += (int)dir;
        maxFrame = 10;

        if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))          FrameReset();
        else if (KEYMANAGER->IsStayKeyDown(VK_LEFT))     Move(DIR::LEFT);

        if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))         FrameReset();
        else if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))    Move(DIR::RIGHT);

        if (KEYMANAGER->IsOnceKeyDown(VK_UP))            FrameReset();
        else if (KEYMANAGER->IsStayKeyDown(VK_UP))       Move(DIR::UP);

        if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))          FrameReset();
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
                weapon->Attack();
                break;
            }
            else
                weapon->ResetAttackCollider();
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
        weapon->Render(hdc);
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
        collider.left -= moveSpeed * DELTATIME;
         
        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
        {
            pos.x -= moveSpeed * DELTATIME;
        }
        break;
    case DIR::UP:
        collider.top -= moveSpeed * DELTATIME;

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
            pos.y -= moveSpeed * DELTATIME;
        break;
    case DIR::RIGHT:
        collider.right += moveSpeed * DELTATIME;

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
            pos.x += moveSpeed * DELTATIME;
        break;
    case DIR::DOWN:
        collider.bottom += moveSpeed * DELTATIME;

        if (COLLIDERMANAGER->CheckCollider(this).size() == 0)
            pos.y += moveSpeed * DELTATIME;
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

    switch (weapon->GetType())
    {
        case WEAPONTYPE::BIGSWORD:
            NextCombo(11, 22, 40);
            AddAttackFrame({ 6,17,28 });
            lpImage = IMAGEMANAGER->FindImage("BigSwordMotion");
            break;
        case WEAPONTYPE::SHORTSWORD:
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

    switch (weapon->GetType())
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
    collider.top = pos.y - lpImage->GetFrameHeight() / 3;
    collider.right = pos.x + lpImage->GetFrameWidth() / 3;
    collider.bottom = pos.y + lpImage->GetFrameHeight() / 3;
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

void Player::EquipmentChagne(Equipment* weapon)
{
    this->weapon = weapon;
}

void Player::ImageLoad()
{
    COLORREF color = RGB(128, 128, 128);

    IMAGEMANAGER->AddImage("PlayerState", L"Image/Player/PlayerState.png",
        640, 832, 10, 13, true, color);
}

void Player::FrameReset()
{
    frameTimer = 0;
    imageFrame = 0;
}   