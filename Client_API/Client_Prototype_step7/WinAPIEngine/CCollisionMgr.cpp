#include "CCollisionMgr.h"
#include "CUnit.h"
#include <windows.h>

SINGLETON_DEFINITION(CCollisionMgr);

CCollisionMgr::CCollisionMgr() {}

CCollisionMgr::~CCollisionMgr() {}

void CCollisionMgr::AddUnit(CUnit* target) {
	m_CollisionUnits.push_back(target);
}

void CCollisionMgr::Update(float deltaTime) {
	std::list<CUnit*>::iterator itFirst, itSecond;
	int count = 0;
	// 반복자를 자신의 다음거 부터 비교하는데 이미 비교한 본인은 다음 비교대상에서 제외하는 비교 알고리즘
	// 버블정렬과 비슷한 모습으로 검사하고 싶을때
	for (itFirst = m_CollisionUnits.begin(); itFirst != m_CollisionUnits.end(); itFirst++) {
		itSecond = itFirst;
		itSecond++;
		for (; itSecond != m_CollisionUnits.end(); itSecond++) {
			if ((*itFirst)->GetIsActive() && (*itSecond)->GetIsActive()) {
				DoCollision((*itFirst), (*itSecond));
			}
		}
	}
}

bool CCollisionMgr::DoCollision(CUnit* tThis, CUnit* other) {

	CCollider* pThis = tThis->GetCollider();
	CCollider* pOther = other->GetCollider();

	bool result = pThis->DoCollision(pOther, 0);
	if (result) {
		bool isBe = pThis->DoCheckBeInCollisions(pOther);
		// 충돌이 일어 난 상태인데, 충돌체 목록에는 아직 등록이 안됬다 == 충돌이 시작 된것
		if (!isBe) {
			pThis->AddToCollisions(pOther);
			pOther->AddToCollisions(pThis);
			OutputDebugString(L"Enter Collision \n");

			pThis->GetOnwerObject()->OnEnterCollision(pOther);
			pOther->GetOnwerObject()->OnEnterCollision(pThis);
		}
		else {
			//OutputDebugString(L"Stay Collision\n");
			pThis->GetOnwerObject()->OnStayCollision(pOther);
			pOther->GetOnwerObject()->OnStayCollision(pThis);
		}
	}
	else if(pThis->DoCheckBeInCollisions(pOther)) {
		// 현재는 충돌 상태가 아니지만 이전에는 충돌
		// 충돌이 끝나는 상태
		pThis->EraseFromCollisions(pOther);
		pOther->EraseFromCollisions(pThis);
		OutputDebugString(L"Exit Collision\n");

		pThis->GetOnwerObject()->OnEndCollision(pOther);
		pOther->GetOnwerObject()->OnEndCollision(pThis);
	}
	

	return false;
}
