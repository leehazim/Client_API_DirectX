#include "CUnit.h"
#include "CAPIEngine.h"

CUnit::CUnit() 
	: m_X(400.0f), m_Y(500.0f), m_Radius(30.0f) {}

CUnit::~CUnit() {}

void CUnit::Render(CAPIEngine* tpEngine) {
	tpEngine->DrawCircle(m_X, m_Y, m_Radius);
}
