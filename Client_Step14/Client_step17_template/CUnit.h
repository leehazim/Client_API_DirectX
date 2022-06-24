#pragma once
#include "CObject.h"

class CTexture;
class CAPIEngine;

class CUnit 
	: public CObject {
public:
	CUnit();
	virtual ~CUnit();

	CUnit(const CUnit& other) {
		m_Position = other.m_Position;
		
		m_Radius = other.m_Radius;

		m_AnchorX = other.m_AnchorX;
		m_AnchorY = other.m_AnchorY;

		m_DisplayX = other.m_DisplayX;
		m_DisplayY = other.m_DisplayY;

		m_Width = other.m_Width;
		m_Height = other.m_Height;

		m_Velocity = other.m_Velocity;

		m_pCTexture = other.m_pCTexture;
		m_pEngine = other.m_pEngine;
	}

	CUnit& operator=(const CUnit& other) {
		m_Position = other.m_Position;
		
		m_Radius = other.m_Radius;
		m_AnchorX = other.m_AnchorX;
		m_AnchorY = other.m_AnchorY;

		m_DisplayX = other.m_DisplayX;
		m_DisplayY = other.m_DisplayY;

		m_Width = other.m_Width;
		m_Height = other.m_Height;

		m_Velocity = other.m_Velocity;

		m_pCTexture = other.m_pCTexture;
		m_pEngine = other.m_pEngine;

		return *this;
	}

public:
	void Render();
	void SetTexture(CTexture* pCtexture);
	
	void SetEngine(CAPIEngine* pEngine);

	void SetAnchors(float anchorX = 0.5f, float anchorY = 0.5f);

	void Update();

	void SetVelocity(SVector2D speed) {
		m_Velocity = speed;
	}
	SVector2D GetVelocity()const {
		return m_Velocity;
	}

	void SetPosition(SVector2D Position) {
		m_Position = Position;
	}
	SVector2D GetPosition()const {
		return m_Position;
	}

public:
	virtual CObject* Clone() = 0;

protected:

	// 반지름
	float m_Radius = 0.0f;

	// Pivot
	float m_AnchorX = 0.5f;
	float m_AnchorY = 0.5f;

	float m_DisplayX = 0.0f;
	float m_DisplayY = 0.0f;

	// 텍스쳐에서 비트맵의 가로 세로를 구해서 Display변수에 피벗된 좌표를 설정
	float m_Width = 0.0f;
	float m_Height = 0.0f;
	
	SVector2D m_Velocity;

	CTexture* m_pCTexture = nullptr;
	CAPIEngine* m_pEngine = nullptr;
};