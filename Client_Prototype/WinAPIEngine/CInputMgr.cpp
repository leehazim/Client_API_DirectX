#include "CInputMgr.h"


// �⺻ �ڵ�
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
/// Ű���� �Է� ���¸� �����ϱ� ���� ���ӷ����󿡼� ��� ���ŵǴ� �Լ�
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
/// ���ϴ� Ű �Է��� �˻��ϴ� �Լ�
/// </summary>
SKeyInfo* CInputMgr::FindKey(const std::string& StrKey) const {
	std::unordered_map<std::string, SKeyInfo*>::const_iterator it = m_MapKeys.find(StrKey);
	
	if (it == m_MapKeys.cend()) {
		return nullptr;
	}

	return it->second;
}

/// <summary>
/// Ű�� ���ȴ°�
/// </summary>
bool CInputMgr::KeyDown(const std::string& StrKey) const {
	SKeyInfo* tpInfo = FindKey(StrKey);
	if (tpInfo == nullptr) {
		return false;
	}

	return tpInfo->m_IsDown;
}

/// <summary>
/// Ű�� �����ִ°�
/// </summary>
bool CInputMgr::KeyPress(const std::string& StrKey) const {
	SKeyInfo* tpInfo = FindKey(StrKey);
	if (tpInfo == nullptr) {
		return false;
	}

	return tpInfo->m_IsPress;
}

/// <summary>
/// Ű�� �ö󰬴°�(������ ����)
/// </summary>
bool CInputMgr::KeyUp(const std::string& StrKey) const {
	SKeyInfo* tpInfo = FindKey(StrKey);
	if (tpInfo == nullptr) {
		return false;
	}

	return tpInfo->m_IsUp;
}
