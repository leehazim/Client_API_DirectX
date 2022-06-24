#pragma once
#include <Windows.h>
#include "macro.h"
#include "CUnit.h"

#define MAX_LOADSTRING					100

class CTexture;
struct SVector2D;

class CAPIEngine {
public:
	CAPIEngine();
	virtual ~CAPIEngine();

	BOOL Create(HINSTANCE, int);
	MSG Run();

	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate(float deltaTime);


	// 원 그리기 행위는 엔진에서 선언 정의
	void DrawCircle(float X, float Y, float Radius);
	void DrawTexture(float X, float Y, CTexture* Texture);
	void Clear(float R = 1.0f, float G = 1.0f, float B = 1.0f);
	void Present();

	float GetDeltaTime() const { return m_DeltaTime; }

	template<typename __type>
	__type* CreatePrefab(CTexture* pText, float anchorX, float anchorY, SVector2D position) {
		__type* pPrefab = new __type();
		pPrefab->SetEngine(this);
		pPrefab->SetTexture(pText);
		pPrefab->SetAnchors(anchorX, anchorY);
		pPrefab->SetPosition(position);
		
		return pPrefab;
	}
	
	void DeletePrefab(CUnit*& prefab) {
		SAFE_DELETE(prefab);
	}

	template<typename __type>
	__type* InstantObject(CUnit* pPrefab) {
		__type* pUnit = static_cast<__type*>(pPrefab->Clone());
		return pUnit;
	}
	template<typename __type>
	void DestroyObject(__type*& unit) {
		SAFE_DELETE(unit);
	}

protected:
	// Create내부 함수랩핑
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static HINSTANCE hInst;

	HWND m_hWnd;
	HDC m_hDC;

	CTexture* m_pBackBuffer;

private:
	CAPIEngine(const CAPIEngine& other) {
		memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));
		memset(szTitle, 0, MAX_LOADSTRING * sizeof(WCHAR));
	}
	CAPIEngine& operator=(const CAPIEngine& other) {}

	float m_ClientWidth;
	float m_ClientHeight;

public:
	float m_DeltaTime = 0.0f;

	LARGE_INTEGER m_Second;
	LARGE_INTEGER m_Time;
};