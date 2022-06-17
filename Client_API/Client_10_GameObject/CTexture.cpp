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

	return true;
}

bool CTexture::CreateBackBuffer(HINSTANCE hInst, HDC hdc) {
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, 800, 600);

	m_OldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

	return true;
}

bool CTexture::CreateBackBuffer(RECT& rt, HINSTANCE hInst, HDC hdc) {
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);

	m_OldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

	return true;
}
