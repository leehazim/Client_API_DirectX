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
	// Create내부 함수랩핑
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];

	static HINSTANCE hInst;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
private:
	CAPIEngine(const CAPIEngine& other) {
		memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));
		memset(szTitle, 0, MAX_LOADSTRING * sizeof(WCHAR));
	}
	CAPIEngine& operator=(const CAPIEngine& other) {}
};