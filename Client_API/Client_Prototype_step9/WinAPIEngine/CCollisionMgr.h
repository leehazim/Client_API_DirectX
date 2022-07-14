#pragma once
#include "macro.h"
#include <list>

class CUnit;

class CCollisionMgr {
	SINGLETON_DECLEARE(CCollisionMgr);

public:
	void AddUnit(CUnit* target);	// 유닛 추가 메소드(충돌판단할 유닛들을 가지고 있다)
	void DeleteUnit(CUnit* target);
	void Update(float deltaTime);	// 어떤 충돌 상태인지 판단하는 메소드

private:
	bool DoCollision(CUnit* tThis, CUnit* other);

private:
	std::list<CUnit*> m_CollisionUnits;
};

