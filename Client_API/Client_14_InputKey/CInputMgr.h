#pragma once
#include "macro.h"

// �⺻ �ڵ�
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