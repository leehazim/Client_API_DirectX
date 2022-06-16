#include "CTexture.h"
#include "CAPIEngine.h"
CTexture::CTexture() 
	: m_hMemDC(nullptr),
	m_hBitmap(nullptr),
	m_OldBitmap(nullptr),
	m_Info({0}) {}

CTexture::~CTexture() {
	SelectObject(m_hMemDC, m_OldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hdc, LPCWSTR path) {
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitmap = (HBITMAP)LoadImage(hInst, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_OldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

	return false;
}