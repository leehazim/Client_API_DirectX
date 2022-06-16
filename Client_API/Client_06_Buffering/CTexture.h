#pragma once
#include <windows.h>
class CAPIEngine;
class CTexture {
public:
	CTexture();
	~CTexture();

	bool LoadTexture(HINSTANCE hInst, HDC hdc, LPCWSTR path);

public:
	HDC m_hMemDC;

	HBITMAP m_hBitmap;
	HBITMAP m_OldBitmap;
	BITMAP m_Info;
};