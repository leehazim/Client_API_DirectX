#include "CInputMgr.h"


// 기본 코딩
SINGLETON_DEFINITION(CInputMgr);

CInputMgr::CInputMgr() {
	m_hWnd = 0;
	m_MapKeys.clear();
	m_pKeyInfo = nullptr;
}

CInputMgr::~CInputMgr() {
	std::unordered_map<std::string, SKeyInfo*>::iterator it;
	for (it = m_MapKeys.begin(); it != m_MapKeys.end(); it++) {
		if ((it->second) != nullptr) {
			delete it->second;
		}
	}
	m_MapKeys.clear();
}

void CInputMgr::Create(HWND hwnd) {
	m_hWnd = hwnd;
}

/// <summary>
/// 키보드 입력 상태를 점검하기 위해 게임루프상에서 계속 갱신되는 함수
/// </summary>
void CInputMgr::Update() {
	std::unordered_map<std::string, SKeyInfo*>::const_iterator it;
	for (it = m_MapKeys.cbegin(); it != m_MapKeys.cend(); it++) {
		int pushCount = 0;

		for (int ti = 0; ti < it->second->m_VecKey.size(); ti++)
			if (GetAsyncKeyState(it->second->m_VecKey[ti]) & 0x8000) {
				pushCount++;
			}

		//if (pushCount >= 1) 
		if(pushCount == it->second->m_VecKey.size()) {
			if (!it->second->m_IsDown && !it->second->m_IsPress) {
				it->second->m_IsDown = true;
			}
			else if (it->second->m_IsDown && !it->second->m_IsPress) {
				it->second->m_IsDown = false;
				it->second->m_IsPress = true;
			}
		}
		else {
			if (it->second->m_IsDown || it->second->m_IsPress) {
				it->second->m_IsDown = false;
				it->second->m_IsPress = false;
				it->second->m_IsUp = true;
			}
			else if (it->second->m_IsUp) {
				it->second->m_IsDown = false;
				it->second->m_IsPress = false;
				it->second->m_IsUp = false;
			}
		}
	}
}

/// <summary>
/// 원하는 키 입력을 검색하는 함수
/// </summary>
SKeyInfo* CInputMgr::FindKey(const std::string& StrKey) const {
	std::unordered_map<std::string, SKeyInfo*>::const_iterator it = m_MapKeys.find(StrKey);
	
	if (it == m_MapKeys.cend()) {
		return nullptr;
	}

	return it->second;
}

/// <summary>
/// 키가 눌렸는가
/// </summary>
bool CInputMgr::KeyDown(const std::string& StrKey) const {
	SKeyInfo* tpInfo = FindKey(StrKey);
	if (tpInfo == nullptr) {
		return false;
	}

	return tpInfo->m_IsDown;
}

/// <summary>
/// 키가 눌려있는가
/// </summary>
bool CInputMgr::KeyPress(const std::string& StrKey) const {
	SKeyInfo* tpInfo = FindKey(StrKey);
	if (tpInfo == nullptr) {
		return false;
	}

	return tpInfo->m_IsPress;
}

/// <summary>
/// 키가 올라갔는가(프레스 종료)
/// </summary>
bool CInputMgr::KeyUp(const std::string& StrKey) const {
	SKeyInfo* tpInfo = FindKey(StrKey);
	if (tpInfo == nullptr) {
		return false;
	}

	return tpInfo->m_IsUp;
}
