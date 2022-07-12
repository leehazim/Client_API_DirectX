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
	// �ݺ��ڸ� �ڽ��� ������ ���� ���ϴµ� �̹� ���� ������ ���� �񱳴�󿡼� �����ϴ� �� �˰���
	// �������İ� ����� ������� �˻��ϰ� ������
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
		// �浹�� �Ͼ� �� �����ε�, �浹ü ��Ͽ��� ���� ����� �ȉ�� == �浹�� ���� �Ȱ�
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
		// ����� �浹 ���°� �ƴ����� �������� �浹
		// �浹�� ������ ����
		pThis->EraseFromCollisions(pOther);
		pOther->EraseFromCollisions(pThis);
		OutputDebugString(L"Exit Collision\n");

		pThis->GetOnwerObject()->OnEndCollision(pOther);
		pOther->GetOnwerObject()->OnEndCollision(pThis);
	}
	

	return false;
}
