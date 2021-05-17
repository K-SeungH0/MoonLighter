#include "Inventory.h"
#include "Image.h"
HRESULT Inventory::Init()
{
    ImageLoad();
    lpImage = IMAGEMANAGER->FindImage("Inventory");
    // 46 -> 82 -> 117 -> 153 
    //가로 36*2 차이
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
    selectSlotX = 0;
    selectSlotY = 0;
    selectSlots.lpSlotImage = IMAGEMANAGER->FindImage("SelectSlot");
    selectSlots.slotPos = invenSlots[selectSlotY][selectSlotX].slotPos;

    return S_OK;
}

void Inventory::Release()
{

}

void Inventory::Update()
{
    if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
    {
        if (--selectSlotX < 0)
            selectSlotX = SLOT_X - 1;
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
    {
        (++selectSlotX) %= SLOT_X;
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_UP))
    {
        if(--selectSlotY < 0)
            selectSlotY = SLOT_Y - 1;
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
    {
        (++selectSlotY) %= SLOT_Y;
    }
    selectSlots.slotPos = invenSlots[selectSlotY][selectSlotX].slotPos;
}

void Inventory::Render(HDC hdc)
{
    if (isActive)
    {
        lpImage->FrameRender(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, 0, 0, IMAGE_SIZE, true);
        
        for (int y = 0; y < SLOT_Y; y++)
        {
            for (int x = 0; x < SLOT_X; x++)
            {
                invenSlots[y][x].lpSlotImage->FrameRender(hdc, invenSlots[y][x].slotPos.x, invenSlots[y][x].slotPos.y, 0, 0, IMAGE_SIZE);
            }
        }
        selectSlots.lpSlotImage->FrameRender(hdc, selectSlots.slotPos.x, selectSlots.slotPos.y, 0, 0, IMAGE_SIZE);
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
}
