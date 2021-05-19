#include "Inventory.h"
#include "Image.h"
HRESULT Inventory::Init()
{
    ImageLoad();
    lpImage = IMAGEMANAGER->FindImage("Inventory");

    this->pos.x = WINSIZE_X / 2;
    this->pos.y = WINSIZE_Y / 2;

    for (int x = 0; x < SLOT_X; x++)
    {
        invenSlots[0][x].lpSlotImage = IMAGEMANAGER->FindImage("InvenSlot");
        invenSlots[0][x].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + 46 * 2 + (x * 36 * 2);
        invenSlots[0][x].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + 39 * 2;
    }

    for (int y = 1; y < SLOT_Y; y++)
    {
        for (int x = 0; x < SLOT_X; x++)
        {
            invenSlots[y][x].lpSlotImage = IMAGEMANAGER->FindImage("InvenSlot");
            invenSlots[y][x].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + 46 * 2 + (x * 36 * 2);
            invenSlots[y][x].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + 82 * 2 + ((y - 1) * 36 * 2);
        }
    }

    equipSlots[0][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (310 * 2);
    equipSlots[0][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (37 * 2);
    equipSlots[0][1].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (397 * 2);
    equipSlots[0][1].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (37 * 2);

    equipSlots[1][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2);
    equipSlots[1][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (82 * 2);

    equipSlots[2][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2);
    equipSlots[2][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (118 * 2);

    equipSlots[2][1].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (304 * 2);
    equipSlots[2][1].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (118 * 2);

    equipSlots[3][0].slotPos.x = WINSIZE_X / 2 - lpImage->GetWidth() + (268 * 2);
    equipSlots[3][0].slotPos.y = WINSIZE_Y / 2 - lpImage->GetHeight() + (154 * 2);

    selectSlotX = 0;
    selectSlotY = 0;
    selectSlots.lpSlotImage = IMAGEMANAGER->FindImage("SelectSlot");
    selectItem.lpSlotImage = IMAGEMANAGER->FindImage("SelectItem");

    selectSlots.slotPos = invenSlots[selectSlotY][selectSlotX].slotPos;

    isEquipSelect = false;
    isItemPickUp = false;
    return S_OK;
}

void Inventory::Release()
{
    delete this;
}

void Inventory::Update()
{
    if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
    {
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
                selectSlotX = SLOT_X - 1;
        }
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
    {
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
        else if(++selectSlotX >= SLOT_X)
        {
            isEquipSelect = !isEquipSelect;
            selectSlotX = 0;
        }
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_UP))
    {
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
                selectSlotY = SLOT_Y - 1;
        }
        else if (--selectSlotY < 0)
            selectSlotY = SLOT_Y - 1;
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
    {
        (++selectSlotY) %= SLOT_Y;

        if (isEquipSelect && selectSlotX)
        {
            if (selectSlotY == 1)
                selectSlotY = 2;
            else if (selectSlotY == 3)
                selectSlotY = 0;
        }
    }

    if (KEYMANAGER->IsOnceKeyDown('J'))
    {
        ItemPickUp();
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

}

void Inventory::Render(HDC hdc)
{
    if (isActive)
    {
        lpImage->FrameRender(hdc, pos.x, pos.y, 0, 0, IMAGE_SIZE, true);
        
        for (int y = 0; y < SLOT_Y; y++)
        {
            for (int x = 0; x < SLOT_X; x++)
            {
                invenSlots[y][x].lpSlotImage->FrameRender(hdc, invenSlots[y][x].slotPos.x, invenSlots[y][x].slotPos.y, 0, 0, IMAGE_SIZE);
            }
        }
        selectSlots.lpSlotImage->FrameRender(hdc, selectSlots.slotPos.x, selectSlots.slotPos.y, 0, 0, IMAGE_SIZE);

        if (isItemPickUp)
            selectItem.lpSlotImage->FrameRender(hdc, selectItem.slotPos.x - 7, selectItem.slotPos.y - 37*2, 0, 0, IMAGE_SIZE);
    }
}

void Inventory::ImageLoad()
{
    COLORREF color = RGB(128, 128, 128); 
    IMAGEMANAGER->AddImage("Inventory", L"Image/UI/Inventory.png",
        519, 274, 1, 1, true, color);
    IMAGEMANAGER->AddImage("InvenSlot", L"Image/UI/Slot.png",
        30, 30, 1, 1, true, color); 
    IMAGEMANAGER->AddImage("SelectSlot", L"Image/UI/SelectSlot.png",
        32, 32, 1, 1, true, color);
    IMAGEMANAGER->AddImage("SelectItem", L"Image/UI/SelectItemSlot.png",
        37, 37, 1, 1, true, color);
}

void Inventory::AddItem(Item* item)
{
    for (int y = 0; y < SLOT_Y; y++)
    {
        for (int x = 0; x < SLOT_X; x++)
        {
            if (invenSlots[y][x].lpItem == nullptr)
            {
                invenSlots[y][x].lpItem = item;
                break;
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
    isItemPickUp = !isItemPickUp;

    if (isEquipSelect)
    {
        selectItem.slotPos = equipSlots[selectSlotY][selectSlotX].slotPos;
    }
    else
    {
        selectItem.slotPos = invenSlots[selectSlotY][selectSlotX].slotPos;
    }
}
