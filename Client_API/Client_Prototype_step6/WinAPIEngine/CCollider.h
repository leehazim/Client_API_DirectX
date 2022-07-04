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
	// �簢 ���� �⵹ü�� �߽��� �׻� �� ������ ����
	SVector2D m_Position;

	float m_Width = 0.f;
	float m_Height = 0.f;

	CObject* m_pObject = nullptr; // ���������� �����ؼ� Collider�� ����
};