#pragma once
#include "macro.h"

// 기본 코딩
//class CInputMgr {
//public:
//	static CInputMgr* GetInstance();
//	static void ReleaseInstance();
//
//private:
//	CInputMgr();
//	~CInputMgr();
//
//private:
//	static CInputMgr* _Instance;
//};

class CInputMgr {
	SINGLETON_DECLEARE(CInputMgr)
};