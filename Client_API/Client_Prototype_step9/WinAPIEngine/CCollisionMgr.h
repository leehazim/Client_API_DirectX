#pragma once
#include "macro.h"
#include <list>

class CUnit;

class CCollisionMgr {
	SINGLETON_DECLEARE(CCollisionMgr);

public:
	void AddUnit(CUnit* target);	// ���� �߰� �޼ҵ�(�浹�Ǵ��� ���ֵ��� ������ �ִ�)
	void DeleteUnit(CUnit* target);
	void Update(float deltaTime);	// � �浹 �������� �Ǵ��ϴ� �޼ҵ�

private:
	bool DoCollision(CUnit* tThis, CUnit* other);

private:
	std::list<CUnit*> m_CollisionUnits;
};

