#pragma once

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
	void Render(CAPIEngine* tpEngine);

public:
	// �������� 2���� ��ǥ�� ������ ���� float
	float m_X = 0.0f;
	float m_Y = 0.0f;

	// ������
	float m_Radius = 0.0f;
};