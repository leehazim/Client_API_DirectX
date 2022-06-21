#include "CInputMgr.h"


// 기본 코딩
CInputMgr* CInputMgr::_Instance = nullptr;

CInputMgr* CInputMgr::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = new CInputMgr();
	}
	
	return _Instance;
}

void CInputMgr::ReleaseInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
	}
}

CInputMgr::CInputMgr() {}

CInputMgr::~CInputMgr() {}
