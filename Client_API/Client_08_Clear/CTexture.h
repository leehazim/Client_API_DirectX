#pragma once
#include <windows.h>
class CAPIEngine;
class CTexture {
public:
	CTexture();
	~CTexture();

	bool LoadTexture(HINSTANCE hInst, HDC hdc, LPCWSTR path);

	bool CreateBackBuffer(HINSTANCE hInst, HDC hdc);
	bool CreateBackBuffer(RECT& rt, HINSTANCE hInst, HDC hdc);
public:
	HDC m_hMemDC;

	HBITMAP m_hBitmap;
	HBITMAP m_OldBitmap;
	BITMAP m_Info;
};