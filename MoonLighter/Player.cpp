#include "Player.h"
#include "Image.h"
#include "Equipment.h"

HRESULT Player::Init()
{
    lpImage = IMAGEMANAGER->FindImage("PlayerState");
    
    moveSpeed = 250;
    
    imageFrame = 0;
    stateFrame = 0;
    maxFrame = 0;

    frameTimer = 0;
    comboStack = 0;
    
    pos = { WINSIZE_X / 2 , WINSIZE_Y / 2 };
    
    isAction = false;
    isCombo = false;

    SetHitBox();
    weapon = new Equipment();
    weapon->Init();

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
    
    if (KEYMANAGER->IsOnceKeyDown('A'))
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

    frameTimer += DELTATIME;
    
    if (frameTimer > 0.1f)
    {
        frameTimer -= 0.1f;
        if (isAction)
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
    
    if (!isAction)
        SetHitBox();
}

void Player::Render(HDC hdc)
{
    Unit::Render(hdc);

    lpImage->FrameRender(hdc, pos.x, pos.y, imageFrame, stateFrame, IMAGE_SIZE, true);

    if(isAction)
        weapon->GetImage()->FrameRender(hdc, pos.x, pos.y, imageFrame, stateFrame, IMAGE_SIZE, true);

    wsprintf(testText, "PreFrame : %d", preFrame);
    TextOut(hdc, 300, 100, testText, strlen(testText));
    wsprintf(testText, "MaxFrame : %d", maxFrame);
    TextOut(hdc, 300, 150, testText, strlen(testText));
}

void Player::Avoid()
{
    isAction = true;
    state = STATE::AVOID;

    moveSpeed = 375;
    stateFrame = 4;
    stateFrame += (int)dir;
    maxFrame = 8;
    hitBox = { 0,0,0,0 };
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
        pos.x -= moveSpeed * DELTATIME;
        break;
    case DIR::UP:
        pos.y -= moveSpeed * DELTATIME;
        break;
    case DIR::RIGHT:
        pos.x += moveSpeed * DELTATIME;
        break;
    case DIR::DOWN:
        pos.y += moveSpeed * DELTATIME;
        break;
    }
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
            // 11 -> 22 -> 40
            NextCombo(11, 22, 40);
            lpImage = IMAGEMANAGER->FindImage("BigSwordMotion");
            break;
        case WEAPONTYPE::SHORTSWORD:
            // 5 -> 9 -> 18
            NextCombo(5, 9, 18);
            lpImage = IMAGEMANAGER->FindImage("ShortSwordMotion");
            break;
        case WEAPONTYPE::GLOVES:
            // 5 -> 10 -> 20            
            NextCombo(5, 10, 20);
            lpImage = IMAGEMANAGER->FindImage("GlovesMotion");
            break;
        case WEAPONTYPE::SPEAR:
            // 6 -> 14 -> 23
            NextCombo(6, 14, 23);
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
    hitBox.left = pos.x - lpImage->GetFrameWidth() / 2;
    hitBox.top = pos.y - lpImage->GetFrameHeight() / 2;
    hitBox.right = pos.x + lpImage->GetFrameWidth() / 2;
    hitBox.bottom = pos.y + lpImage->GetFrameHeight() / 2;
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

void Player::EquipmentChagne(Equipment* weapon)
{
    this->weapon = weapon;
}

void Player::FrameReset()
{
    frameTimer = 0;
    imageFrame = 0;
}   