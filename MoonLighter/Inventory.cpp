#include "Inventory.h"
#include "Image.h"
#include "Item.h"
#include "Player.h"

HRESULT Inventory::Init()
{
    ImageLoad();
    lpImage = IMAGEMANAGER->FindImage("Inventory");
    jBtn = IMAGEMANAGER->FindImage("J_Button");
    iBtn = IMAGEMANAGER->FindImage("I_Button");
    lpDescriptionImage = IMAGEMANAGER->FindImage("Description");

    this->pos.x = WINSIZE_X / 2;
    this->pos.y = WINSIZE_Y / 2;
    int offset = 32;
    for (int x = 0; x < INVEN_SIZE_X; x++)
    {
        //invenSlots[0][x].lpSlotImage = IMAGEMANAGER->FindImage("InvenSlot");
        invenSlots[0][x].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + 46 * 2 + (x * 36 * 2) + offset + 1;
        invenSlots[0][x].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + 39 * 2 + offset;
    }

    for (int y = 1; y < INVEN_SIZE_Y; y++)
    {
        for (int x = 0; x < INVEN_SIZE_X; x++)
        {
            //invenSlots[y][x].lpSlotImage = IMAGEMANAGER->FindImage("InvenSlot");
            invenSlots[y][x].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + 46 * 2 + (x * 36 * 2) + offset + 1;
            invenSlots[y][x].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + 82 * 2 + ((y - 1) * 36 * 2) + offset;
        }
    }

    equipSlots[0][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (310 * 2) + offset + 1;
    equipSlots[0][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (37 * 2) + offset;
    equipSlots[0][1].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (397 * 2) + offset + 1;
    equipSlots[0][1].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (37 * 2) + offset;

    equipSlots[1][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2) + offset + 1;
    equipSlots[1][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (82 * 2) + offset;

    equipSlots[2][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2) + offset + 1;
    equipSlots[2][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (118 * 2) + offset;

    equipSlots[2][1].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (304 * 2) + offset + 1;
    equipSlots[2][1].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (118 * 2) + offset;

    equipSlots[3][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2) + offset + 1;
    equipSlots[3][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (154 * 2) + offset;

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

        lpImage->FrameRender(hdc, pos.x, pos.y, 0, 0, IMAGE_SIZE, true);

        HFONT hFont;
        HFONT oldFont;
        hFont = CreateFont(32, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("나눔스퀘어_ac Bold"));
        oldFont = (HFONT)SelectObject(hdc, hFont);
        SetBkColor(hdc, RGB(0, 0, 0));
        jBtn->FrameRender(hdc, pos.x - 400, WINSIZE_Y - 50, 0, 0, IMAGE_SIZE, true);
        wsprintf(text, "잡기 / 길게 눌러서 묶음 잡기");
        TextOut(hdc, pos.x - 400 + 48, WINSIZE_Y - 50 - 15, text, strlen(text));
        iBtn->FrameRender(hdc, pos.x + 200, WINSIZE_Y - 50, 0, 0, IMAGE_SIZE, true);
        wsprintf(text, "닫기");
        TextOut(hdc, pos.x + 200 + 48, WINSIZE_Y - 50 - 15, text, strlen(text));

        SelectObject(hdc, oldFont);
        DeleteObject(hFont);

        SetTextColor(hdc, RGB(0, 0, 0));

        for (int y = 0; y < INVEN_SIZE_Y; y++)
        {
            for (int x = 0; x < INVEN_SIZE_X; x++)
            {
                //invenSlots[y][x].lpSlotImage->FrameRender(hdc, invenSlots[y][x].slotPos.x, invenSlots[y][x].slotPos.y, 0, 0, IMAGE_SIZE, true);
                if (invenSlots[y][x].lpItem != nullptr)
                {
                    invenSlots[y][x].lpItem->Render(hdc, { invenSlots[y][x].slotPos.x, invenSlots[y][x].slotPos.y });

                    if (!invenSlots[y][x].lpItem->GetItemData().isEquipment)
                    {
                        wsprintf(text, to_string(invenSlots[y][x].count).c_str());
                        TextOut(hdc, invenSlots[y][x].slotPos.x + 15, invenSlots[y][x].slotPos.y + 15, text, strlen(text));
                    }
                }
            }
        }
        for (int y = 0; y < INVEN_SIZE_Y; y++)
        {
            for (int x = 0; x < 2; x++)
            {
                if (equipSlots[y][x].lpItem != nullptr)
                    equipSlots[y][x].lpItem->Render(hdc, { equipSlots[y][x].slotPos.x, equipSlots[y][x].slotPos.y });
            }
        }

       selectSlots.lpSlotImage->FrameRender(hdc, selectSlots.slotPos.x, selectSlots.slotPos.y, 0, 0, selectSlotSize, true);
       if (isEquipSelect)
       {
           if (equipSlots[selectSlotY][selectSlotX].lpItem)
           {
               lpDescriptionImage->FrameRender(hdc, pos.x - 50, WINSIZE_Y - 100, 0, 0, 1, true);

               hFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("나눔스퀘어_ac Bold"));
               oldFont = (HFONT)SelectObject(hdc, hFont);

               string description = equipSlots[selectSlotY][selectSlotX].lpItem->GetDescription();
               wsprintf(text, description.c_str());               
               TextOut(hdc, pos.x - 50 - (description.size() * 12 / 2), WINSIZE_Y - 110, text, strlen(text));
               
               SelectObject(hdc, oldFont);
               DeleteObject(hFont);
           }
       }
       else
       {
           if (invenSlots[selectSlotY][selectSlotX].lpItem)
           {
               lpDescriptionImage->FrameRender(hdc, pos.x - 50, WINSIZE_Y - 100, 0, 0, 1, true);

               hFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("나눔스퀘어_ac Bold"));
               oldFont = (HFONT)SelectObject(hdc, hFont);

               string description = invenSlots[selectSlotY][selectSlotX].lpItem->GetDescription();
               wsprintf(text, description.c_str());
               TextOut(hdc, pos.x - 50 - (description.size() * 12 / 2), WINSIZE_Y - 110, text, strlen(text));

               SelectObject(hdc, oldFont);
               DeleteObject(hFont);
           }
       }
        if (isItemPickUp)
        {
            selectItem.lpSlotImage->FrameRender(hdc, selectItem.slotPos.x - 7, selectItem.slotPos.y - 37 * 2, 0, 0, IMAGE_SIZE, true);
            selectItem.lpItem->Render(hdc, { selectItem.slotPos.x - 7, selectItem.slotPos.y - 37 * 2 });
            if (!selectItem.lpItem->GetItemData().isEquipment)
            {
                wsprintf(text, to_string(selectItem.count).c_str());
                SetTextColor(hdc, RGB(0, 0, 0));
                TextOut(hdc, selectItem.slotPos.x - 7 + 15, selectItem.slotPos.y - 37 * 2 + 15, text, strlen(text));
            }
        }


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
                invenSlots[y][x].count++;
                isAddItem = true;
                break;
            }
            else if (invenSlots[y][x].lpItem->GetItemData().itemCode == item->GetItemData().itemCode)
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
            equipSlots[selectSlotY][selectSlotX].lpItem = nullptr;

            GAMEDATA->GetRunTimePlayer()->EquipmentChagne(nullptr);
            selectItem.count++;
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
            equipSlots[selectSlotY][selectSlotX].lpItem = nullptr;

            selectItem.count++;
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
            if (equipSlots[selectSlotY][selectSlotX].lpItem)
            {
                Item* tmepItem = equipSlots[selectSlotY][selectSlotX].lpItem;

                equipSlots[selectSlotY][selectSlotX].lpItem = selectItem.lpItem;
                selectItem.lpItem = tmepItem;
                GAMEDATA->GetRunTimePlayer()->EquipmentChagne(equipSlots[selectSlotY][selectSlotX].lpItem);
                isItemPickUp = true;
            }
            else
            {
                equipSlots[selectSlotY][selectSlotX].lpItem = selectItem.lpItem;
                selectItem.lpItem = nullptr;
                selectItem.count = 0;
                GAMEDATA->GetRunTimePlayer()->EquipmentChagne(equipSlots[selectSlotY][selectSlotX].lpItem);
                isItemPickUp = false;
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


    // 장비 아이콘
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