#include "Image.h"
#include <gdiplus.h>

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);
    
    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = FALSE;
    this->transColor = FALSE;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height,
    bool isTransparent/* = FALSE*/, COLORREF transColor/* = FALSE*/)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
     imageInfo->hBitmap =
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    // 알파 블랜드
    imageInfo->hBlendDC = CreateCompatibleDC(hdc);
    imageInfo->hBlendBit = CreateCompatibleBitmap(hdc,
        imageInfo->width, imageInfo->height);
    imageInfo->hOldBlendBit = (HBITMAP)SelectObject(imageInfo->hBlendDC,
        imageInfo->hBlendBit);

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    this->blendFunc.AlphaFormat = 0;
    this->blendFunc.BlendFlags = 0;
    this->blendFunc.BlendOp = AC_SRC_OVER;
    this->blendFunc.SourceConstantAlpha = 255;

    return S_OK;
}

HRESULT Image::Init(const wchar_t* fileName, int maxFrameX, int maxFrameY)
{
    HDC hdc = GetDC(g_hWnd);
    COLORREF color = RGB(128, 128, 128);

    this->isTransparent = true;
    this->transColor = color;

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);     

    Gdiplus::GdiplusStartupInput gpStartupInput;
    ULONG_PTR gpToken;
    Gdiplus::GdiplusStartup(&gpToken, &gpStartupInput, NULL);
    Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(fileName, false);

    auto height = bitmap->GetHeight();
    auto width = bitmap->GetWidth();

    if (bitmap)
    {
        int R = GetRValue(transColor);
        int G = GetGValue(transColor);
        int B = GetBValue(transColor);
        bitmap->GetHBITMAP(RGB(B,G,R), &imageInfo->hBitmap);
        delete bitmap;
    }
    
    Gdiplus::GdiplusShutdown(gpToken);

    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    // 알파 블랜드
    imageInfo->hBlendDC = CreateCompatibleDC(hdc);
    imageInfo->hBlendBit = CreateCompatibleBitmap(hdc,
        imageInfo->width, imageInfo->height);
    imageInfo->hOldBlendBit = (HBITMAP)SelectObject(imageInfo->hBlendDC,
        imageInfo->hBlendBit);

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }


    this->blendFunc.AlphaFormat = 0;
    this->blendFunc.BlendFlags = 0;
    this->blendFunc.BlendOp = AC_SRC_OVER;
    this->blendFunc.SourceConstantAlpha = 255;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap =
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY, float size, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2) * size;
        y = destY - (imageInfo->height / 2) * size;
    }

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width * size, imageInfo->height * size,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        if (size > 1)
        {
            StretchBlt(hdc,
                x, y,
                imageInfo->frameWidth * size,
                imageInfo->frameHeight * size,
                imageInfo->hMemDC,
                imageInfo->frameWidth * imageInfo->currFrameX,
                imageInfo->frameHeight * imageInfo->currFrameY,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                SRCCOPY
            );
        }
        else
        {
            // bitmap 에 있는 이미지 정보를 다른 비트맵에 복사
            BitBlt(
                hdc,                // 복사 목적지 DC
                x, y,               // 복사 시작 위치
                imageInfo->width * size,   // 원본에서 복사될 가로크기
                imageInfo->height * size,  // 원본에서 복사될 세로크기
                imageInfo->hMemDC,  // 원본 DC
                0, 0,               // 원본에서 복사 시작 위치
                SRCCOPY             // 복사 옵션
            );
        }
    }
}

void Image::CameraRender(HDC hdc, int destX, int destY, int cameraX, int cameraY, float size, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->width / 2) * size;
        y = destY - (imageInfo->height / 2) * size;
    }

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,
            x,
            y,
            min(imageInfo->width * size, WINSIZE_X),
            min(imageInfo->height * size, WINSIZE_Y),

            imageInfo->hMemDC,
            imageInfo->width* size > WINSIZE_X ? cameraX : 0,
            imageInfo->height * size > WINSIZE_Y ? cameraY : 0,
            min(imageInfo->width * size, WINSIZE_X),
            min(imageInfo->height * size, WINSIZE_Y),
            transColor
        );
    }
    else
    {
        if (size > 1)
        {
            StretchBlt(hdc,
                x, y,
                imageInfo->frameWidth * size,
                imageInfo->frameHeight * size,
                imageInfo->hMemDC,
                imageInfo->frameWidth * imageInfo->currFrameX,
                imageInfo->frameHeight * imageInfo->currFrameY,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                SRCCOPY
            );
        }
        else
        {
            // bitmap 에 있는 이미지 정보를 다른 비트맵에 복사
            BitBlt(
                hdc,                // 복사 목적지 DC
                x, y,               // 복사 시작 위치
                imageInfo->width * size,   // 원본에서 복사될 가로크기
                imageInfo->height * size,  // 원본에서 복사될 세로크기
                imageInfo->hMemDC,  // 원본 DC
                0, 0,               // 원본에서 복사 시작 위치
                SRCCOPY             // 복사 옵션
            );
        }
    }
}

void Image::FrameRender(HDC hdc, int destX, int destY,
    int currFrameX, int currFrameY, float size, bool isCenterRenderring)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->frameWidth / 2) * size;
        y = destY - (imageInfo->frameHeight / 2) * size;
    }

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,                // 목적지 DC
            x, y,               // 복사 위치
            imageInfo->frameWidth * size,
            imageInfo->frameHeight * size,  // 복사 크기

            imageInfo->hMemDC,  // 원본 DC
            imageInfo->frameWidth * imageInfo->currFrameX,  // 복사 X 위치
            imageInfo->frameHeight * imageInfo->currFrameY, // 복사 Y 위치
            imageInfo->frameWidth, 
            imageInfo->frameHeight,  // 복사 크기
            transColor  // 제외할 색상
        );
    }
    else
    {
        if (size > 1)
        {
            StretchBlt(hdc,
                x, y,
                imageInfo->frameWidth * size,
                imageInfo->frameHeight * size,
                imageInfo->hMemDC,
                imageInfo->frameWidth * imageInfo->currFrameX,
                imageInfo->frameHeight * imageInfo->currFrameY,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                SRCCOPY
            );
        }
        else
        {
            BitBlt(
                hdc,
                x, y,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                imageInfo->hMemDC,
                imageInfo->frameWidth * imageInfo->currFrameX,
                imageInfo->frameHeight * imageInfo->currFrameY,
                SRCCOPY
            );
        }
    }
}

void Image::CutRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, int cutX, int cutY, float size, bool isCenterRenderring)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->frameWidth / 2) * size;
        y = destY - (imageInfo->frameHeight / 2) * size;
    }

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,                // 목적지 DC
            x, y,               // 복사 위치
            imageInfo->frameWidth * size - cutX,
            imageInfo->frameHeight * size - cutY,  // 복사 크기

            imageInfo->hMemDC,  // 원본 DC
            imageInfo->frameWidth * imageInfo->currFrameX,  // 복사 X 위치
            imageInfo->frameHeight * imageInfo->currFrameY + cutY / 2, // 복사 Y 위치
            imageInfo->frameWidth - cutX,
            imageInfo->frameHeight - cutY / 2,  // 복사 크기
            transColor  // 제외할 색상
        );
    }
    else
    {
        if (size > 1)
        {
            StretchBlt(hdc,
                x, y,
                imageInfo->frameWidth * size,
                imageInfo->frameHeight * size,
                imageInfo->hMemDC,
                imageInfo->frameWidth * imageInfo->currFrameX,
                imageInfo->frameHeight * imageInfo->currFrameY,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                SRCCOPY
            );
        }
        else
        {
            BitBlt(
                hdc,
                x, y,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                imageInfo->hMemDC,
                imageInfo->frameWidth * imageInfo->currFrameX,
                imageInfo->frameHeight * imageInfo->currFrameY,
                SRCCOPY
            );
        }
    }
}

void Image::AlphaRender(HDC hdc, int destX, int destY,int currFrameX, int currFrameY, float size, bool isCenterRenderring)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x = destX - (imageInfo->frameWidth / 2) * size;
        y = destY - (imageInfo->frameHeight / 2) * size;
    }

    BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, hdc, x, y, SRCCOPY); 

    GdiTransparentBlt(
        imageInfo->hBlendDC, 
        0, 0,   
        imageInfo->frameWidth * size, 
        imageInfo->frameHeight * size,
        imageInfo->hMemDC, 
        imageInfo->frameWidth * imageInfo->currFrameX,  
        imageInfo->frameHeight * imageInfo->currFrameY, 
        imageInfo->frameWidth,
        imageInfo->frameHeight,  
        transColor
    );

    AlphaBlend(hdc, x, y, imageInfo->width, imageInfo->height, imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        if (imageInfo->hBlendDC != NULL)
        {
            SelectObject(imageInfo->hBlendDC, imageInfo->hOldBlendBit);
            DeleteObject(imageInfo->hBlendBit);
            DeleteDC(imageInfo->hBlendDC);
        }

        delete imageInfo;
        imageInfo = nullptr;
    }
}
