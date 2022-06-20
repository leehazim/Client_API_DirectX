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
	// �������� 2���� ��ǥ�� ������ ���� float
	float m_X = 0.0f;
	float m_Y = 0.0f;

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
	// ����� nullptr�� �ʱ�ȭ �ϴ� ������ ������
	CTexture* m_pCTexture = nullptr;
};