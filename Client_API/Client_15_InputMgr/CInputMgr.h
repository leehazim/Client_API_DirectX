#pragma once
#include "macro.h"

#include <typeinfo>
#include <string>
#include <windows.h>
#include <unordered_map> // �ؽ����̺� �ڷᱸ���� �Ϲ�ȭ �ڷᱸ���� �����

struct SKeyInfo {
	std::string m_StrName = "";	// Ű
	DWORD m_KeyInput = 0;		// ������

	bool m_IsDown;
	bool m_IsPress;
	bool m_IsUp;

	SKeyInfo() :
		m_IsDown(false),
		m_IsPress(false),
		m_IsUp(false) {}
};

class CInputMgr {
	SINGLETON_DECLEARE(CInputMgr);

public:
	virtual void Create(HWND hwnd);
	void Update();

	SKeyInfo* FindKey(const std::string& StrKey)const;

	// ������ ���ε� Ű�� ���¸� Ȯ���ϴ� �Լ�
	bool KeyDown(const std::string& StrKey) const;
	bool KeyPress(const std::string& StrKey) const;
	bool KeyUp(const std::string& StrKey) const;

	template <typename __type>
	bool AddKey(const std::string& InputName, __type data) {
		// InputName �ؽ�ȭ
		if (!m_pKeyInfo) {
			m_pKeyInfo = new SKeyInfo();
		}

		// ���ø����� �޾��� Ÿ���� ������ �˾ƿ��� ������
		const char* tpType = typeid(__type).name();
		if (strcmp(tpType, "char") == 0 ||
			strcmp(tpType, "int") == 0) {
			m_pKeyInfo->m_KeyInput = (DWORD)data;
		}
		else {
			return false;
		}

		// �ؽ�ȭ�� Ű�� Ű���嵥���� ����
		m_pKeyInfo->m_StrName = InputName;

		// �����̳ʿ� �߰�
		m_MapKeys.insert(
			make_pair(InputName, m_pKeyInfo));

		if (m_pKeyInfo) {
			m_pKeyInfo = nullptr; // �����ʹ� �����̳ʿ� ��������� �����̳ʿ��� ����� �ǰ� ������ ����� ���� nullptr�� �ٲ۴�.
		}

		return true;
	}

private:
	HWND m_hWnd;

	std::unordered_map<std::string, SKeyInfo*> m_MapKeys;
	SKeyInfo* m_pKeyInfo = nullptr;
};

