#include "Inventory.h"
#include "Image.h"
#include "Item.h"
#include "Player.h"

HRESULT Inventory::Init()
{
    ImageLoad();
    lpImage = IMAGEMANAGER->FindImage("Inventory");
    lpJBtnImage = IMAGEMANAGER->FindImage("J_Button");
    lpIBtnImage = IMAGEMANAGER->FindImage("I_Button");
    lpDescriptionImage = IMAGEMANAGER->FindImage("Description");
    lpCurrentWeaponImage = IMAGEMANAGER->FindImage("MainWeapon");

    this->pos.x = WINSIZE_X / 2;
    this->pos.y = WINSIZE_Y / 2;

    int offset = 32;
    for (int x = 0; x < INVEN_SIZE_X; x++)
    {
        invenSlots[0][x].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + 46 * 2 + (x * 36 * 2) + offset + 1;
        invenSlots[0][x].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + 39 * 2 + offset;
        invenSlots[0][x].slotType = SLOTTYPE::INVEN;
    }

    for (int y = 1; y < INVEN_SIZE_Y; y++)
    {
        for (int x = 0; x < INVEN_SIZE_X; x++)
        {
            invenSlots[y][x].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + 46 * 2 + (x * 36 * 2) + offset + 1;
            invenSlots[y][x].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + 82 * 2 + ((y - 1) * 36 * 2) + offset;
            invenSlots[y][x].slotType = SLOTTYPE::INVEN;
        }
    }

    equipSlots[0][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (310 * 2) + offset + 1;
    equipSlots[0][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (37 * 2) + offset;
    equipSlots[0][0].slotType = SLOTTYPE::MAINWEAPON;

    equipSlots[0][1].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (397 * 2) + offset + 1;
    equipSlots[0][1].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (37 * 2) + offset;
    equipSlots[0][1].slotType = SLOTTYPE::SUBWEAPON;

    equipSlots[1][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2) + offset + 1;
    equipSlots[1][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (82 * 2) + offset;
    equipSlots[1][0].slotType = SLOTTYPE::HELMET;

    equipSlots[2][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2) + offset + 1;
    equipSlots[2][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (118 * 2) + offset;
    equipSlots[2][0].slotType = SLOTTYPE::CHEST;

    equipSlots[2][1].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (304 * 2) + offset + 1;
    equipSlots[2][1].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (118 * 2) + offset;
    equipSlots[2][1].slotType = SLOTTYPE::POTION;

    equipSlots[3][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2) + offset + 1;
    equipSlots[3][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (154 * 2) + offset;
    equipSlots[3][0].slotType = SLOTTYPE::SHOES;

    selectSlotX = 0;
    selectSlotY = 0;
    selectSlots.lpSlotImage = IMAGEMANAGER->FindImage("SelectSlot");
    selectItem.lpSlotImage = IMAGEMANAGER->FindImage("SelectItem");

    selectSlots.slotPos = invenSlots[selectSlotY][selectSlotX].slotPos;

    isEquipSelect = false;
    isItemPickUp = false;
    selectSlotSize = IMAGE_SIZE;
    selectTimer = 0;

    return S_OK;
}

void Inventory::Release()
{
    for (int y = 0; y < INVEN_SIZE_Y; y++)
    {
        for (int x = 0; x < INVEN_SIZE_X; x++)
        {
            if (invenSlots[y][x].lpItem != nullptr)
            {
                delete invenSlots[y][x].lpItem;
                invenSlots[y][x].lpItem = nullptr;
            }
        }
    }

    for (int y = 0; y < INVEN_SIZE_Y; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            if (equipSlots[y][x].lpItem != nullptr)
            {
                delete equipSlots[y][x].lpItem;
                equipSlots[y][x].lpItem = nullptr;
            }
        }
    }

    delete this;
}

void Inventory::Update()
{
    if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
    {
        selectSlotSize = IMAGE_SIZE * 1.5f;
        selectTimer = 0;

        if (--selectSlotX < 0)
        {
            isEquipSelect = !isEquipSelect;
            if (isEquipSelect)
            {
                if(selectSlotY % 2 == 0)
                    selectSlotX = 1;
                else
                    selectSlotX = 0;
            }
            else
                selectSlotX = INVEN_SIZE_X - 1;
        }
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
    {
        selectSlotSize = IMAGE_SIZE * 1.5f;
        selectTimer = 0;

        if (isEquipSelect)
        {
            if (selectSlotY % 2 != 0)
            {
                if (++selectSlotX > 0)
                {
                    isEquipSelect = !isEquipSelect;
                    selectSlotX = 0;
                }
            }
            else if (++selectSlotX > 1)
            {
                isEquipSelect = !isEquipSelect;
                selectSlotX = 0;
            }

        }
        else if(++selectSlotX >= INVEN_SIZE_X)
        {
            isEquipSelect = !isEquipSelect;
            selectSlotX = 0;
        }
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_UP))
    {
        selectSlotSize = IMAGE_SIZE * 1.5f;
        selectTimer = 0;

        if (isEquipSelect)
        {
            --selectSlotY;
            if (selectSlotX)
            {
                if (selectSlotY == -1)
                {
                    selectSlotY = 2;
                }
                else if (selectSlotY == 1)
                {
                    selectSlotY = 0;
                }
            }
            else if(selectSlotY < 0)
                selectSlotY = INVEN_SIZE_Y - 1;
        }
        else if (--selectSlotY < 0)
            selectSlotY = INVEN_SIZE_Y - 1;
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
    {
        selectSlotSize = IMAGE_SIZE * 1.5f;
        selectTimer = 0;

        (++selectSlotY) %= INVEN_SIZE_Y;
        if (isEquipSelect && selectSlotX)
        {
            if (selectSlotY == 1)
                selectSlotY = 2;
            else if (selectSlotY == 3)
                selectSlotY = 0;
        }
    }

    if (KEYMANAGER->IsStayKeyDown('J'))
    {
        selectTimer += DELTATIME;
        if(selectTimer >= 0.25f)
            ItemAllPickUp();
    }
    
    if (KEYMANAGER->IsOnceKeyUp('J'))
    {
        if (selectTimer < 0.25f)
        {
            if (!isItemPickUp)
                ItemPickUp();
            else
                ItemPickDown();
        }
        selectTimer = 0;
    }

    if (isEquipSelect)
    {
        selectSlots.slotPos = equipSlots[selectSlotY][selectSlotX].slotPos;
        selectItem.slotPos = equipSlots[selectSlotY][selectSlotX].slotPos;
    }
    else
    {
        selectSlots.slotPos = invenSlots[selectSlotY][selectSlotX].slotPos;
        selectItem.slotPos = invenSlots[selectSlotY][selectSlotX].slotPos;
    }

    selectSlotSize -= 10 * DELTATIME;
    if (selectSlotSize < IMAGE_SIZE)
        selectSlotSize = IMAGE_SIZE;
}

void Inventory::Render(HDC hdc)
{
    if (isActive)
    {
        lpImage->Render(hdc, pos.x, pos.y, IMAGE_SIZE, true);

        lpJBtnImage->Render(hdc, pos.x - 400, WINSIZE_Y - 50, IMAGE_SIZE, true);
        FLOATINGFONT->Render(hdc, { pos.x - 400 + 48, WINSIZE_Y - 50 - 15 }, 32, "잡기 / 길게 눌러서 묶음 잡기", RGB(255, 255, 255));
        
        lpIBtnImage->Render(hdc, pos.x + 200, WINSIZE_Y - 50, IMAGE_SIZE, true);
        FLOATINGFONT->Render(hdc, { pos.x + 200 + 48, WINSIZE_Y - 50 - 15 }, 32, "닫기", RGB(255, 255, 255));

        lpCurrentWeaponImage->Render(hdc, 890, 205, IMAGE_SIZE, true);

        for (int y = 0; y < INVEN_SIZE_Y; y++)
        {
            for (int x = 0; x < INVEN_SIZE_X; x++)
            {
                if (invenSlots[y][x].lpItem != nullptr)
                {
                    invenSlots[y][x].lpItem->Render(hdc, { invenSlots[y][x].slotPos.x, invenSlots[y][x].slotPos.y });

                    invenSlots[y][x].lpItem->SetSaveCount(invenSlots[y][x].count);
                    invenSlots[y][x].lpItem->SetSaveSlotPos({ x,y });
                    invenSlots[y][x].lpItem->SetOnwer(&invenSlots[y][x]);
                    if (!invenSlots[y][x].lpItem->GetItemData().isEquipment || invenSlots[y][x].lpItem->GetSlotType() == SLOTTYPE::POTION)
                    {
                        FLOATINGFONT->Render(hdc, { invenSlots[y][x].slotPos.x + 15, invenSlots[y][x].slotPos.y + 15 }, 12, to_string(invenSlots[y][x].count).c_str(), RGB(0, 0, 0));
                    }
                }
            }
        }
        for (int y = 0; y < INVEN_SIZE_Y; y++)
        {
            for (int x = 0; x < 2; x++)
            {
                if (equipSlots[y][x].lpItem != nullptr)
                {
                    equipSlots[y][x].lpItem->Render(hdc, { equipSlots[y][x].slotPos.x, equipSlots[y][x].slotPos.y });

                    equipSlots[y][x].lpItem->SetSaveCount(equipSlots[y][x].count);
                    equipSlots[y][x].lpItem->SetSaveSlotPos({ x,y });
                    equipSlots[y][x].lpItem->SetOnwer(&equipSlots[y][x]);

                    if (equipSlots[y][x].slotType == SLOTTYPE::POTION)
                    {
                        if(equipSlots[y][x].count != 0)
                            FLOATINGFONT->Render(hdc, { equipSlots[y][x].slotPos.x + 15, invenSlots[y][x].slotPos.y + 15 }, 12, to_string(equipSlots[y][x].count).c_str(), RGB(0, 0, 0));
                        else
                        {

                        }
                    }
                }
            }
        }

       selectSlots.lpSlotImage->FrameRender(hdc, selectSlots.slotPos.x, selectSlots.slotPos.y, 0, 0, selectSlotSize, true);
       if (isEquipSelect)
       {
           if (equipSlots[selectSlotY][selectSlotX].lpItem)
           {
               lpDescriptionImage->FrameRender(hdc, pos.x - 50, WINSIZE_Y - 100, 0, 0, 1, true);

               FLOATINGFONT->Render(hdc, { pos.x - 50 - ((LONG)equipSlots[selectSlotY][selectSlotX].lpItem->GetDescription().size() * 12 / 2), WINSIZE_Y - 110 }, 24, equipSlots[selectSlotY][selectSlotX].lpItem->GetDescription().c_str(), RGB(0,0,0));
           }
       }
       else
       {
           if (invenSlots[selectSlotY][selectSlotX].lpItem)
           {
               lpDescriptionImage->FrameRender(hdc, pos.x - 50, WINSIZE_Y - 100, 0, 0, 1, true);
               
               FLOATINGFONT->Render(hdc, { pos.x - 50 - ((LONG)invenSlots[selectSlotY][selectSlotX].lpItem->GetDescription().size() * 12 / 2), WINSIZE_Y - 110 }, 24, invenSlots[selectSlotY][selectSlotX].lpItem->GetDescription().c_str(), RGB(0, 0, 0));
           }
       }
        if (isItemPickUp)
        {
            selectItem.lpSlotImage->FrameRender(hdc, selectItem.slotPos.x - 7, selectItem.slotPos.y - 37 * 2, 0, 0, IMAGE_SIZE, true);
            selectItem.lpItem->Render(hdc, { selectItem.slotPos.x - 7, selectItem.slotPos.y - 37 * 2 });
            FLOATINGFONT->Render(hdc, { selectItem.slotPos.x - 7 + 15, selectItem.slotPos.y - 37 * 2 + 15 }, 12, to_string(selectItem.count).c_str(), RGB(0, 0, 0));
        }

        FLOATINGFONT->Render(hdc, { 1095, 285 }, 24, to_string(GAMEDATA->GetRunTimePlayer()->GetMaxHp() + GAMEDATA->GetRunTimePlayer()->GetAdditionalHp()).c_str(), RGB(0, 0, 0));
        FLOATINGFONT->Render(hdc, { 1095, 285 + 62 }, 24, to_string(GAMEDATA->GetRunTimePlayer()->GetDamage()).c_str(), RGB(0, 0, 0));
        FLOATINGFONT->Render(hdc, { 1095, 285 + 123 }, 24, to_string(GAMEDATA->GetRunTimePlayer()->GetArmor() + GAMEDATA->GetRunTimePlayer()->GetAdditionalArmor()).c_str(), RGB(0, 0, 0));
        FLOATINGFONT->Render(hdc, { 1095, 285 + 183 }, 24, to_string(GAMEDATA->GetRunTimePlayer()->GetMoveSpeed() + GAMEDATA->GetRunTimePlayer()->GetAdditionalMoveSpeed()).c_str(), RGB(0, 0, 0));
    }
}


void Inventory::AddItem(Item* item)
{
    bool isAddItem = false;
    for (int y = 0; y < INVEN_SIZE_Y; y++)
    {
        for (int x = 0; x < INVEN_SIZE_X; x++)
        {
            if (invenSlots[y][x].lpItem == nullptr)
            {
                invenSlots[y][x].lpItem = new Item();
                invenSlots[y][x].lpItem->Init(item->GetItemData(), item->GetItemManager());
                invenSlots[y][x].lpItem->SetOnwer(&invenSlots[y][x]);
                invenSlots[y][x].count++;
                isAddItem = true;
                break;
            }
            else if ((invenSlots[y][x].lpItem->GetItemData().itemCode == item->GetItemData().itemCode) 
                && (item->GetSlotType() != SLOTTYPE::INVEN || item->GetSlotType() != SLOTTYPE::POTION))
            {
                invenSlots[y][x].count++;
                isAddItem = true;
                break;
            }
        }
        if (isAddItem)
            break;
    }
}

void Inventory::RemoveItem(Item* item)
{
    for (int y = 0; y < INVEN_SIZE_Y; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            if (item == equipSlots[y][x].lpItem)
            {
                delete equipSlots[y][x].lpItem;
                equipSlots[y][x].lpItem = nullptr;
                GAMEDATA->GetRunTimePlayer()->EquipFromInventory(equipSlots[y][x].slotType, equipSlots[y][x].lpItem);
            }
        }
    }
}

void Inventory::ToggleActive()
{
     this->isActive = !(this->isActive);
     selectSlotX = 0;
     selectSlotY = 0;
     isEquipSelect = false;
}

void Inventory::ItemPickUp()
{
    selectSlotSize = IMAGE_SIZE * 1.5f;
    selectTimer = 0;

    if (isEquipSelect)
    {
        if (equipSlots[selectSlotY][selectSlotX].lpItem)
        {
            selectItem.lpItem = equipSlots[selectSlotY][selectSlotX].lpItem;
            //equipSlots[selectSlotY][selectSlotX].lpItem = nullptr;
            
            equipSlots[selectSlotY][selectSlotX].count--;
            selectItem.count++;

            if (equipSlots[selectSlotY][selectSlotX].count == 0)
                equipSlots[selectSlotY][selectSlotX].lpItem = nullptr;

            GAMEDATA->GetRunTimePlayer()->EquipFromInventory(equipSlots[selectSlotY][selectSlotX].slotType, equipSlots[selectSlotY][selectSlotX].lpItem);
            isItemPickUp = true;
        }
    }
    else
    {
        if (invenSlots[selectSlotY][selectSlotX].lpItem)
        {
            selectItem.lpItem = invenSlots[selectSlotY][selectSlotX].lpItem;

            invenSlots[selectSlotY][selectSlotX].count--;
            selectItem.count++;

            if(invenSlots[selectSlotY][selectSlotX].count == 0)
                invenSlots[selectSlotY][selectSlotX].lpItem = nullptr;

            isItemPickUp = true;
        }
    }
}

void Inventory::ItemAllPickUp()
{
    if (isEquipSelect)
    {
        selectSlotSize = IMAGE_SIZE * 1.5f;

        if (equipSlots[selectSlotY][selectSlotX].lpItem)
        {

            selectItem.lpItem = equipSlots[selectSlotY][selectSlotX].lpItem;
            selectItem.count += equipSlots[selectSlotY][selectSlotX].count;

            equipSlots[selectSlotY][selectSlotX].lpItem = nullptr;
            equipSlots[selectSlotY][selectSlotX].count = 0;
            GAMEDATA->GetRunTimePlayer()->EquipFromInventory(equipSlots[selectSlotY][selectSlotX].slotType, equipSlots[selectSlotY][selectSlotX].lpItem);
            isItemPickUp = true;
        }
    }
    else
    {
        if (invenSlots[selectSlotY][selectSlotX].lpItem)
        {
            if (isItemPickUp)
            {
                if (selectItem.lpItem->GetItemData().itemCode == invenSlots[selectSlotY][selectSlotX].lpItem->GetItemData().itemCode)
                {
                    selectSlotSize = IMAGE_SIZE * 1.5f;
                    selectItem.count += invenSlots[selectSlotY][selectSlotX].count;
                    invenSlots[selectSlotY][selectSlotX].lpItem = nullptr;
                    invenSlots[selectSlotY][selectSlotX].count = 0;
                }
                else
                {
                    ItemPickDown();
                }
            }
            else
            {
                if(selectItem.lpItem)
                {
                    Item* tmepItem = selectItem.lpItem;
                    int tempCount = selectItem.count;
                    selectItem.lpItem = invenSlots[selectSlotY][selectSlotX].lpItem;
                    selectItem.count = invenSlots[selectSlotY][selectSlotX].count;

                    invenSlots[selectSlotY][selectSlotX].lpItem = tmepItem;
                    invenSlots[selectSlotY][selectSlotX].count = tempCount;
                }
                else 
                {
                    selectSlotSize = IMAGE_SIZE * 1.5f;
                    selectItem.lpItem = invenSlots[selectSlotY][selectSlotX].lpItem;
                    selectItem.count = invenSlots[selectSlotY][selectSlotX].count;
                    invenSlots[selectSlotY][selectSlotX].lpItem = nullptr;
                    invenSlots[selectSlotY][selectSlotX].count = 0;
                }
            }
            isItemPickUp = true;
        }
    }
}

void Inventory::ItemPickDown()
{
    selectSlotSize = IMAGE_SIZE * 1.5f;
    selectTimer = 0;

    if (isEquipSelect)
    {
        if (selectItem.lpItem->GetItemData().isEquipment)
        {
            // 장착된 아이템이 있으면
            if (equipSlots[selectSlotY][selectSlotX].lpItem)
            {
                if (selectItem.lpItem->GetSlotType() == equipSlots[selectSlotY][selectSlotX].slotType ||
                    (selectItem.lpItem->GetSlotType() == SLOTTYPE::MAINWEAPON && equipSlots[selectSlotY][selectSlotX].slotType == SLOTTYPE::SUBWEAPON))
                {
                    
                    if (equipSlots[selectSlotY][selectSlotX].lpItem->GetItemData().itemCode == selectItem.lpItem->GetItemData().itemCode)
                    {
                        ItemPickUp();
                        return;
                    }
                    
                    Item* tempItem = equipSlots[selectSlotY][selectSlotX].lpItem;
                    int tempCount = equipSlots[selectSlotY][selectSlotX].count;

                    equipSlots[selectSlotY][selectSlotX].lpItem = selectItem.lpItem;
                    equipSlots[selectSlotY][selectSlotX].count = selectItem.count;
                    selectItem.lpItem = tempItem;
                    selectItem.count = tempCount;

                    GAMEDATA->GetRunTimePlayer()->EquipFromInventory(equipSlots[selectSlotY][selectSlotX].slotType, equipSlots[selectSlotY][selectSlotX].lpItem);
                    isItemPickUp = true;
                }
            }
            else
            {
                if (selectItem.lpItem->GetSlotType() == equipSlots[selectSlotY][selectSlotX].slotType ||
                    (selectItem.lpItem->GetSlotType() == SLOTTYPE::MAINWEAPON && equipSlots[selectSlotY][selectSlotX].slotType == SLOTTYPE::SUBWEAPON))
                {
                    equipSlots[selectSlotY][selectSlotX].lpItem = selectItem.lpItem;
                    equipSlots[selectSlotY][selectSlotX].count = selectItem.count;

                    equipSlots[selectSlotY][selectSlotX].lpItem->SetSaveCount(equipSlots[selectSlotY][selectSlotX].count);

                    selectItem.lpItem = nullptr;
                    selectItem.count = 0;
                    GAMEDATA->GetRunTimePlayer()->EquipFromInventory(equipSlots[selectSlotY][selectSlotX].slotType, equipSlots[selectSlotY][selectSlotX].lpItem);

                    isItemPickUp = false;
                }
            }
        }
    }
    else
    {
        isItemPickUp = false;

        if (invenSlots[selectSlotY][selectSlotX].lpItem != nullptr)
        {
            if (invenSlots[selectSlotY][selectSlotX].lpItem->GetItemData().itemCode == selectItem.lpItem->GetItemData().itemCode)
            {
                ItemPickUp();
                return;
            }
        }

        if (invenSlots[selectSlotY][selectSlotX].lpItem)
        {
            Item* tmepItem = selectItem.lpItem;
            int tempCount = selectItem.count;
            selectItem.lpItem = invenSlots[selectSlotY][selectSlotX].lpItem;
            selectItem.count = invenSlots[selectSlotY][selectSlotX].count;

            invenSlots[selectSlotY][selectSlotX].lpItem = tmepItem;
            invenSlots[selectSlotY][selectSlotX].count = tempCount;
            isItemPickUp = true;
        }
        else 
        {
            invenSlots[selectSlotY][selectSlotX].lpItem = selectItem.lpItem;
            invenSlots[selectSlotY][selectSlotX].count = selectItem.count;

            selectItem.lpItem = nullptr;
            selectItem.count = 0;
        }
    }
}

void Inventory::SwapWeapon()
{
    if (lpCurrentWeaponImage == IMAGEMANAGER->FindImage("MainWeapon"))
        lpCurrentWeaponImage = IMAGEMANAGER->FindImage("SubWeapon");
    else
        lpCurrentWeaponImage = IMAGEMANAGER->FindImage("MainWeapon");
}

void Inventory::DataLoad(ItemManager* lpItemManager)
{
    auto items = GAMEDATA->GetItems();

    for (auto iter = items.begin(); iter != items.end(); iter++)
    {
        if ((*iter).isEquipment)
        {
            if (equipSlots[(*iter).slotPos.y][(*iter).slotPos.x].lpItem == nullptr)
            {
                equipSlots[(*iter).slotPos.y][(*iter).slotPos.x].lpItem = new Item();
                equipSlots[(*iter).slotPos.y][(*iter).slotPos.x].lpItem->Init((*iter), lpItemManager);
            }
            else
            {

            }

        }
        else
        {
            if (invenSlots[(*iter).slotPos.y][(*iter).slotPos.x].lpItem == nullptr)
            {
                invenSlots[(*iter).slotPos.y][(*iter).slotPos.x].lpItem = new Item();
                invenSlots[(*iter).slotPos.y][(*iter).slotPos.x].lpItem->Init((*iter), lpItemManager);
            }
            else
            {

            }
        }
    }
}

void Inventory::ImageLoad()
{
    // 인벤 UI
    IMAGEMANAGER->AddImage("Inventory", L"Image/UI/Inventory.png");
    IMAGEMANAGER->AddImage("InvenSlot", L"Image/UI/Slot.png");
    IMAGEMANAGER->AddImage("SelectSlot", L"Image/UI/SelectSlot.png");
    IMAGEMANAGER->AddImage("SelectItem", L"Image/UI/SelectItemSlot.png");
    IMAGEMANAGER->AddImage("J_Button", L"Image/UI/J_Button.png");
    IMAGEMANAGER->AddImage("I_Button", L"Image/UI/I_Button.png");
    IMAGEMANAGER->AddImage("Description", L"Image/UI/Inventory_Description.png");
    IMAGEMANAGER->AddImage("MainWeapon", L"Image/UI/Inventory_MainWeapon.png");
    IMAGEMANAGER->AddImage("SubWeapon", L"Image/UI/Inventory_SubWeapon.png");

    // 무기 아이콘
    IMAGEMANAGER->AddImage("BigSword_0", L"Image/Item/BigSword_0.png");
    IMAGEMANAGER->AddImage("BigSword_1", L"Image/Item/BigSword_1.png");
    IMAGEMANAGER->AddImage("Bow_0", L"Image/Item/Bow_0.png");
    IMAGEMANAGER->AddImage("Bow_1", L"Image/Item/Bow_1.png");
    IMAGEMANAGER->AddImage("Gloves_0", L"Image/Item/Gloves_0.png");
    IMAGEMANAGER->AddImage("Gloves_1", L"Image/Item/Gloves_1.png");
    IMAGEMANAGER->AddImage("ShortSword_0", L"Image/Item/ShortSword_0.png");
    IMAGEMANAGER->AddImage("ShortSword_1", L"Image/Item/ShortSword_1.png");
    IMAGEMANAGER->AddImage("Spear_0", L"Image/Item/Spear_0.png");
    IMAGEMANAGER->AddImage("Spear_1", L"Image/Item/Spear_1.png");

    // 방어구 아이콘
    IMAGEMANAGER->AddImage("Boot_0", L"Image/Item/Boot_0.png");
    IMAGEMANAGER->AddImage("Boot_1", L"Image/Item/Boot_1.png");
    IMAGEMANAGER->AddImage("Helmet_0", L"Image/Item/Helmet_0.png");
    IMAGEMANAGER->AddImage("Helmet_1", L"Image/Item/Helmet_1.png");
    IMAGEMANAGER->AddImage("Chest_0", L"Image/Item/Chest_0.png");
    IMAGEMANAGER->AddImage("Chest_1", L"Image/Item/Chest_1.png");

    // 잡템 아이콘
    IMAGEMANAGER->AddImage("Item_0", L"Image/Item/Item_0.png");
    IMAGEMANAGER->AddImage("Item_1", L"Image/Item/Item_1.png");
    IMAGEMANAGER->AddImage("Item_2", L"Image/Item/Item_2.png");
    IMAGEMANAGER->AddImage("Item_3", L"Image/Item/Item_3.png");
    IMAGEMANAGER->AddImage("Item_4", L"Image/Item/Item_4.png");
    IMAGEMANAGER->AddImage("Item_5", L"Image/Item/Item_5.png");
    IMAGEMANAGER->AddImage("Item_6", L"Image/Item/Item_6.png");
    IMAGEMANAGER->AddImage("Item_7", L"Image/Item/Item_7.png");
    IMAGEMANAGER->AddImage("Item_8", L"Image/Item/Item_8.png");
    IMAGEMANAGER->AddImage("Item_9", L"Image/Item/Item_9.png");
    IMAGEMANAGER->AddImage("Item_10", L"Image/Item/Item_10.png");
    IMAGEMANAGER->AddImage("Item_11", L"Image/Item/Item_11.png");
    IMAGEMANAGER->AddImage("Item_12", L"Image/Item/Item_12.png");

    // 포션 아이콘
    IMAGEMANAGER->AddImage("Potion_0", L"Image/Item/Potion_0.png");
    IMAGEMANAGER->AddImage("Potion_1", L"Image/Item/Potion_1.png");
    IMAGEMANAGER->AddImage("Potion_2", L"Image/Item/Potion_2.png");
    IMAGEMANAGER->AddImage("Potion_3", L"Image/Item/Potion_3.png");
}