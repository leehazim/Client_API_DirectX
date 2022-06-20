#pragma once

class CTexture;
class CAPIEngine;
class CUnit {
public:
	CUnit();
	~CUnit();

	CUnit(const CUnit& unit) {
		m_X = unit.m_X;
		m_Y = unit.m_Y;
		m_Radius = unit.m_Radius;
	}
	void operator=(const CUnit& unit) {
		m_X = unit.m_X;
		m_Y = unit.m_Y;
		m_Radius = unit.m_Radius;
	}

public:
	void Render(CAPIEngine* pEngine);
	void SetTexture(CTexture* pCtexture);
	
	void SetAnchors(float anchorX = 0.5f, float anchorY = 0.5f);
public:
	// 연속적이 2차원 좌표를 가지기 위해 float
	float m_X = 0.0f;
	float m_Y = 0.0f;

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
	// 선언시 nullptr로 초기화 하는 습관을 들이자
	CTexture* m_pCTexture = nullptr;
};