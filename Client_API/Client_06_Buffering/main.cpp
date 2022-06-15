#include "CAPIEngine.h"
#include "CUnit.h"
class LSHEngine
	: public CAPIEngine {
public:
	LSHEngine() 
		: m_Unit(nullptr) {}
	virtual ~LSHEngine() {}

public:
	virtual void OnCreate() override {
		CAPIEngine::OnCreate();
		// TODO : ���� �ʱ�ȭ

		WCHAR szTemp[256] = L"";
		wsprintf(szTemp, L"LSHEngine::OnCreate\n");
		OutputDebugString(szTemp);

		m_Unit = new CUnit();
	}

	virtual void OnDestroy() override {
		// TODO : ���� ����

		if (m_Unit != nullptr) {
			delete m_Unit;
		}

		CAPIEngine::OnDestroy();
	}

	virtual void OnUpdate() override {
		CAPIEngine::OnUpdate();
		
		// input
		// �޽��� �������� DispatchMessage�� �Ⱥ������� �Ǵ� �ǰ�
		if (GetAsyncKeyState('A') & 0x8000) {
			m_Unit->m_X = m_Unit->m_X - 0.01f;
			//m_Unit->m_X -= 0.01f;
		}

		if (GetAsyncKeyState('D') & 0x8000) {
			m_Unit->m_X = m_Unit->m_X + 0.01f;
			//m_Unit->m_X += 0.01f;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			OutputDebugString(L"Skill_00\n");
			MessageBox(nullptr, L"Skill_00", L"Skill_00", MB_OK);
		}
		// update


		// render
		m_Unit->Render(this);

		//test
		// ��Ʈ�� �׸������� ȣȯ�Ǵ� �޸�DC����, ���Ϸκ��� ��Ʈ�� �ҷ�����
		HDC MemDC = CreateCompatibleDC(this->m_hDC);
		HBITMAP hBitmap = (HBITMAP)LoadImage(hInst, L"resources/bongbong_0.bmp",
											 IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		// �׸����� ��Ʈ���� �޸� DC�� ä���, ��Ʈ�� �ٲ�ġ�� ������ �ٲ����ش�.
		HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
		BITMAP bit;
		GetObject(hBitmap, sizeof(BITMAP), &bit);
		BitBlt(this->m_hDC, 100, 100, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);

		// ����̳��� GDI Object���� ����
		SelectObject(MemDC, OldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(MemDC);
	}

private:
	LSHEngine(const LSHEngine& other) {}
	LSHEngine& operator=(const LSHEngine& other) {}

public:
	CUnit* m_Unit = nullptr;
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	LSHEngine Game;
	Game.Create(hInstance, nCmdShow);
	MSG msg = Game.Run();

	return (int)msg.wParam;
}