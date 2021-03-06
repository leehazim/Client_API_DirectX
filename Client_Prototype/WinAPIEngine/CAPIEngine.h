#pragma once
#include <Windows.h>
#include "macro.h"
#include "CUnit.h"
#include "CCollisionMgr.h"

#define MAX_LOADSTRING					100

#pragma comment(lib,"msimg32.lib")

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

	void DrawCircle(float X, float Y, float Radius);
	/*void DrawTexture(float X, float Y, CTexture* Texture);*/
	// 컬러키를 매개변수로 받을 수 있도록 정의 변경
	void DrawTexture(float X, float Y, CTexture*, COLORREF color = RGB(255, 255, 255));
	// 스프라이트 시트를 이용해서 그리는 함수 
	void DrawSprite(float x, float y, CTexture* texture,
					int row, int col, int index, COLORREF colorKey = RGB(255, 255, 255));
	void Clear(float R = 1.0f, float G = 1.0f, float B = 1.0f);
	void Present();

	float GetDeltaTime() const { return m_DeltaTime; }

	template<typename __type>
	__type* CreatePrefab(CTexture* pText, float anchorX, float anchorY, SVector2D position);
	void DeletePrefab(CUnit*& prefab);

	template<typename __type>
	__type* InstantObject(CUnit* pPrefab);
	template<typename __type>
	void DestroyObject(__type*& unit);

	float GetClientWidth() const;
	float GetClientHeight() const;

	HDC GetHDC() const { return m_hDC; }
	HINSTANCE GetHInst() const { return hInst; }

protected:
	// Create내부 함수랩핑
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
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

template<typename __type>
inline __type* CAPIEngine::CreatePrefab(CTexture* pText, float anchorX, float anchorY, SVector2D position) {
	__type* pPrefab = new __type();
	pPrefab->Create(this);
	pPrefab->SetTexture(pText);
	pPrefab->SetAnchors(anchorX, anchorY);
	pPrefab->SetPosition(position);

	pPrefab->SetColliderPos();
	pPrefab->SetIsActive(true);

	return pPrefab;
}

template<typename __type>
inline __type* CAPIEngine::InstantObject(CUnit* pPrefab) {
	__type* pUnit = static_cast<__type*>(pPrefab->Clone());
	CCollisionMgr::GetInstance()->AddUnit(pUnit);
	return pUnit;
}

template<typename __type>
inline void CAPIEngine::DestroyObject(__type*& unit) {
	CCollisionMgr::GetInstance()->DeleteUnit(unit);
	SAFE_DELETE(unit);
}
