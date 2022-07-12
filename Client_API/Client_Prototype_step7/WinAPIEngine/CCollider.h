#pragma once
#include "SVector2D.h"
#include <list>

class CObject;

class CCollider {
public:
	CCollider();
	CCollider(const CCollider& collider);
	void operator =(const CCollider& collider);
	~CCollider();

	bool DoCollisionby(CObject* other);
	bool DoCollision(CCollider* colliderOther, int);
	void Create(SVector2D position, float width, float height);
	void Update();

	void SetPosition(SVector2D position);
	void SetSize(float width, float height);

	void SetOnwerObject(CObject* pObject);
	CObject* GetOnwerObject() const;
	
	SVector2D GetPosition() const {
		return m_Position;
	}

	// 관리 리스트에 충돌체들 추가 제거 포함된 충돌체인지 검사
	void AddToCollisions(CCollider* pCollider);
	void EraseFromCollisions(CCollider* pCollider);
	bool DoCheckBeInCollisions(CCollider* pCollider);

private:
	bool DoCollisionAABB(CCollider* other);
	bool DoCollisionAABB(CObject* other, int n);

private:
	SVector2D m_Position;

	float m_Width = 0.f;
	float m_Height = 0.f;

	CObject* m_pObject = nullptr; // 지속적으로 참조해서 Collider를 설정

	// 충돌체 정보 목록: 충돌이 어느 시점의 상태인지 검토하기위한 변수
	std::list<CCollider*> m_Collisions;
};