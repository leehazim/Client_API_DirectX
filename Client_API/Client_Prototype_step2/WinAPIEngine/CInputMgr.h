#pragma once
#include "macro.h"

#include <typeinfo>
#include <string>
#include <windows.h>
#include <vector>
#include <unordered_map> // 해쉬테이블 자료구조를 일반화 자료구조로 만든것

struct SKeyInfo {
	std::string m_StrName = "";	// 키
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

	// 현재의 매핑된 키의 상태를 확인하는 함수
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

	// InputName 해시화
	if (!m_pKeyInfo) {
		m_pKeyInfo = new SKeyInfo();
	}

	// 템플릿으로 받아진 타입의 정보를 알아오는 연산자
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

	// 재귀호출 recursive case
	AddKey(arg...);

	if (m_pKeyInfo) {
		m_pKeyInfo = nullptr; // 포인터는 컨테이너에 들어있으니 컨테이너에서 지우면 되고 다음에 사용을 위해 nullptr로 바꾼다.
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
