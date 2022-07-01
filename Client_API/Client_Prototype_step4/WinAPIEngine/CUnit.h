#pragma once
#include "CObject.h"

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

public:
	virtual CObject* Clone() = 0;

protected:

	// ������
	float m_Radius = 0.0f;

	// Pivot
	float m_AnchorX = 0.5f;
	float m_AnchorY = 0.5f;

	float m_DisplayX = 0.0f;
	float m_DisplayY = 0.0f;

	// �ؽ��Ŀ��� ��Ʈ���� ���� ���θ� ���ؼ� Display������ �ǹ��� ��ǥ�� ����
	float m_Width = 0.0f;
	float m_Height = 0.0f;

	bool m_IsActive = false;
	
	SVector2D m_Velocity;

	CTexture* m_pCTexture = nullptr;
	CAPIEngine* m_pEngine = nullptr;
};