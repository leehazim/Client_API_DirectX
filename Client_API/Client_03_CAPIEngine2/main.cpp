#include "CAPIEngine.h"

class LSHEngine 
	: public CAPIEngine {
public:
	LSHEngine() {

	}
	virtual ~LSHEngine() {

	}

public:
	virtual void OnCreate() override {
		CAPIEngine::OnCreate();
		// TODO : ���� �ʱ�ȭ

		WCHAR szTemp[256] = L"";
		wsprintf(szTemp, L"LSHEngine::OnCreate\n");
		OutputDebugString(szTemp);
	}
	virtual void OnDestroy() override {
		// TODO : ���� ����

		CAPIEngine::OnDestroy();
	}
	virtual void OnUpdate() override {
		CAPIEngine::OnUpdate();
		// TODO : ���� ����
		// ������۸� ����
		TextOut(m_hDC, 0, 0, L"Test Text", lstrlen(L"Test Text"));
		TextOut(m_hDC, 0, 25, L"Hi Window", lstrlen(L"Hi Window"));
		TextOut(m_hDC, 0, 50, L"�ȳ��ϼ���", lstrlen(L"�ȳ��ϼ���"));

		LPCWSTR tString = L"WCHAR string";
		TextOut(m_hDC, 0, 75, tString, lstrlen(tString));

		Rectangle(m_hDC, 100, 100, 200, 200);

		MoveToEx(m_hDC, 100, 100, NULL);
		LineTo(m_hDC, 200, 200);

		Ellipse(m_hDC, 210, 100, 310, 200);

		// ������۸� ����
		/*RECT rt;
		GetClientRect(m_hWnd, &rt);

		HDC MemDC = CreateCompatibleDC(m_hDC);
		HBITMAP MemBit = CreateCompatibleBitmap(m_hDC, rt.right, rt.bottom);
		HBITMAP OldBitmap;
		OldBitmap = (HBITMAP)SelectObject(MemDC, MemBit);
		FillRect(MemDC, &rt, (HBRUSH)(COLOR_WINDOW + 1));
		TextOut(MemDC, 0, 0, L"Test Text", lstrlen(L"Test Text"));
		TextOut(MemDC, 0, 25, L"Hi Window", lstrlen(L"Hi Window"));
		TextOut(MemDC, 0, 50, L"�ȳ��ϼ���", lstrlen(L"�ȳ��ϼ���"));

		LPCWSTR tString = L"WCHAR string";
		TextOut(MemDC, 0, 75, tString, lstrlen(tString));

		Rectangle(MemDC, 100, 100, 200, 200);

		MoveToEx(MemDC, 100, 100, NULL);
		LineTo(MemDC, 200, 200);

		Ellipse(MemDC, 210, 100, 310, 200);
		BitBlt(m_hDC, 0, 0, rt.right, rt.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, OldBitmap);
		DeleteDC(MemDC);*/
	}

private:
	LSHEngine(const LSHEngine& other) {}
	LSHEngine& operator=(const LSHEngine& other) {}
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	LSHEngine Game;
	Game.Create(hInstance, nCmdShow);
	MSG msg = Game.Run();

	return (int)msg.wParam;
}