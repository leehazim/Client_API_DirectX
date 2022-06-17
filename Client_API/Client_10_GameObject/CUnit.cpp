#include "CUnit.h"
#include "CAPIEngine.h"
#include "CTexture.h"

CUnit::CUnit() 
	: m_X(400.0f), m_Y(500.0f), m_Radius(30.0f), m_pCTexture(nullptr) {}

CUnit::~CUnit() {}

void CUnit::Render(CAPIEngine* pEngine) {

	m_Width = m_pCTexture->m_Info.bmWidth;
	m_Height = m_pCTexture->m_Info.bmHeight;

	m_DisplayX = m_X - m_Width * m_AnchorX;
	m_DisplayY = m_Y - m_Height * m_AnchorY;

	pEngine->DrawTexture(m_DisplayX, m_DisplayY, m_pCTexture);
	//tpEngine->DrawTexture(m_X, m_Y, m_pCTexture);
}

void CUnit::SetTexture(CTexture* pCTexture) {
	m_pCTexture = pCTexture;
}

void CUnit::SetAnchors(float anchorX, float anchorY) {
	m_AnchorX = anchorX;
	m_AnchorY = anchorY;
}
