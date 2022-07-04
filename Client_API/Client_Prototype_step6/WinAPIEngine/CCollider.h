#pragma once
#include "SVector2D.h"

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
	
	/*SVector2D GetPosition() const {
		return m_Position;
	}*/
private:
	bool DoCollisionAABB(CCollider* other);
	bool DoCollisionAABB(CObject* other, int n = 1);

private:
	// 사각 영역 출돌체의 중심은 항상 정 가운데라고 가정
	SVector2D m_Position;

	float m_Width = 0.f;
	float m_Height = 0.f;

	CObject* m_pObject = nullptr; // 지속적으로 참조해서 Collider를 설정
};