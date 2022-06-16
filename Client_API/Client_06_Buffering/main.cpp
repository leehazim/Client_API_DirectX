#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"

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

		m_Ctexture = new CTexture();
		m_Ctexture->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbong_0.bmp");
	}

	virtual void OnDestroy() override {
		// TODO : ���� ����

		if (m_Ctexture != nullptr) {
			delete m_Ctexture;
			m_Ctexture = nullptr;
		}

		if (m_Unit != nullptr) {
			delete m_Unit;
			m_Unit = nullptr;
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
		// CTexture�� �޾Ƴ��� ��Ʈ�� �������� �޾ƿͼ� �׸���
		// �׸��� ���� ����ϴ� ����(�Ŵ���)Ŭ������ ����� ����
		// �ؽ�ó���� ��� �����̳ʿ� Ŭ������ ���� �����ϴ� ������� �����ϴ� ����(�����)�� �����ϰ� ������ ����.
		BitBlt(this->m_hDC, 
			   m_Unit->m_X, m_Unit->m_Y,
			   m_Ctexture->m_Info.bmWidth, m_Ctexture->m_Info.bmHeight, 
			   m_Ctexture->m_hMemDC, 0, 0, SRCCOPY);

		// 06.16 ���� �׽�Ʈ ������ ����
		//test
		// ��Ʈ�� �׸������� ȣȯ�Ǵ� �޸�DC����, ���Ϸκ��� ��Ʈ�� �ҷ�����
		//HDC MemDC = CreateCompatibleDC(this->m_hDC);
		//HBITMAP hBitmap = (HBITMAP)LoadImage(hInst, L"resources/bongbong_0.bmp",
		//									 IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		//HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
		//BITMAP bit;
		//GetObject(hBitmap, sizeof(BITMAP), &bit);
		//
		//// �׸����� ��Ʈ���� �޸� DC�� ä���, ��Ʈ�� �ٲ�ġ�� ������ �ٲ����ش�.
		//BitBlt(this->m_hDC, 100, 100, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);
		//
		//// ����̳��� GDI Object���� ����
		//SelectObject(MemDC, OldBitmap);
		//DeleteObject(hBitmap);
		//DeleteDC(MemDC);
	}

public:
	CUnit* m_Unit = nullptr;
	CTexture* m_Ctexture = nullptr;

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