#pragma once
#include <Windows.h>
#include "resource.h"

#define MAX_LOADSTRING					100

class CAPIEngine {
public:
	CAPIEngine();
	virtual ~CAPIEngine();

	BOOL Create(HINSTANCE, int);
	MSG Run();

	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate();

protected:
	// Create���� �Լ�����
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];

	static HINSTANCE hInst;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
};