#pragma once
#include "CObject.h"
#include "CCollider.h"
#include <vector>

class CTexture;
class CAPIEngine;

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

	CCollider* GetCollider() const;

public:
	virtual CObject* Clone() = 0;

protected:

	// ¹ÝÁö¸§
	float m_Radius = 0.0f;

	float m_DisplayX = 0.0f;
	float m_DisplayY = 0.0f;

	bool m_IsActive = false;
	
	SVector2D m_Velocity;

	CTexture* m_pCTexture = nullptr;
	CAPIEngine* m_pEngine = nullptr;

protected:
	CCollider* m_pCollider = nullptr;
};