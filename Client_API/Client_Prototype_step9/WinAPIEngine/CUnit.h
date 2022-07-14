#pragma once
#include "CObject.h"
#include "CCollider.h"
#include <vector>

class CTexture;
class CAPIEngine;
class CAnimator;

class CUnit 
	: public CObject {
public:
	CUnit();
	CUnit(const CUnit& other);
	CUnit& operator=(const CUnit& other);
	virtual ~CUnit();

public:
	virtual void Create(CAPIEngine* pEngine);
	virtual void Destroy();

	virtual void Update(float deltaTime);
	virtual void Render();

	void SetTexture(CTexture* pCtexture);
	void SetEngine(CAPIEngine* pEngine);
	void SetAnchors(float anchorX = 0.5f, float anchorY = 0.5f);

	void SetVelocity(SVector2D speed);
	SVector2D GetVelocity() const;

	void SetIsActive(bool isActive);
	bool GetIsActive() const;

	void SetRadius(float radius);
	float GetRadius() const;

	float GetDisplayX() const { return m_DisplayX; }
	float GetDisplayY() const { return m_DisplayY; }

	CCollider* GetCollider() const;

public:
	virtual CObject* Clone() = 0;

	virtual void OnEnterCollision(CCollider* other) override {}
	virtual void OnStayCollision(CCollider* other)	override {}
	virtual void OnEndCollision(CCollider* other) 	override {}

	void SetColliderPos() {
		m_pCollider->SetPosition(this->GetPosition());
	}

	CAnimator* CreateAnimator(const std::string id, CAPIEngine* pEngine);
	void DestroyAnimator();

protected:
	float m_Radius = 0.0f;

	float m_DisplayX = 0.0f;
	float m_DisplayY = 0.0f;

	bool m_IsActive = false;
	
	SVector2D m_Velocity;

	CTexture* m_pCTexture = nullptr;
	CAPIEngine* m_pEngine = nullptr;

protected:
	CCollider* m_pCollider = nullptr;
	CAnimator* m_pAnimator = nullptr;
};