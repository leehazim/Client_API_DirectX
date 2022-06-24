#pragma once
#include "macro.h"

#include <typeinfo>
#include <string>
#include <windows.h>
#include <vector>
#include <unordered_map> // �ؽ����̺� �ڷᱸ���� �Ϲ�ȭ �ڷᱸ���� �����

struct SKeyInfo {
	std::string m_StrName = "";	// Ű
	std::vector<DWORD> m_VecKey;

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

	template<typename __type>
	bool AddKey(const __type& data); 

	template<typename __type, typename... Types>
	bool AddKey(const __type& data, const Types&... arg);

private:
	HWND m_hWnd;

	std::unordered_map<std::string, SKeyInfo*> m_MapKeys;
	SKeyInfo* m_pKeyInfo = nullptr;
};

template<typename __type, typename... Types>
inline bool CInputMgr::AddKey(const __type& data, const Types&... arg) {

	// InputName �ؽ�ȭ
	if (!m_pKeyInfo) {
		m_pKeyInfo = new SKeyInfo();
	}

	// ���ø����� �޾��� Ÿ���� ������ �˾ƿ��� ������
	const char* tpType = typeid(__type).name();
	if (strcmp(tpType, "char") == 0 ||
		strcmp(tpType, "int") == 0) {
		m_pKeyInfo->m_VecKey.push_back((DWORD)data);
	}
	else {
		m_pKeyInfo->m_StrName = data;
		m_MapKeys.insert(
			make_pair(m_pKeyInfo->m_StrName, m_pKeyInfo));
	}

	// ���ȣ�� recursive case
	AddKey(arg...);

	if (m_pKeyInfo) {
		m_pKeyInfo = nullptr; // �����ʹ� �����̳ʿ� ��������� �����̳ʿ��� ����� �ǰ� ������ ����� ���� nullptr�� �ٲ۴�.
	}

	return true;
}

template<typename __type>
inline bool CInputMgr::AddKey(const __type& data) {
	const char* pType = typeid(__type).name();
	if (strcmp(pType, "char") == 0 ||
		strcmp(pType, "int") == 0) {
		m_pKeyInfo->m_VecKey.push_back((DWORD)data);
	}
	else {
		m_pKeyInfo->m_StrName = data;
		m_MapKeys.insert(
			make_pair(m_pKeyInfo->m_StrName, m_pKeyInfo));
	}

	return true;
}
