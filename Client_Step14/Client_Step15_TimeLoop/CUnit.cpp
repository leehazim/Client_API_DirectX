#include "CUnit.h"
#include "CAPIEngine.h"
#include "CTexture.h"

CUnit::CUnit() :
	CObject(),
	m_Radius(30.0f),
	m_pCTexture(nullptr),
	m_pEngine(nullptr),
	m_Velocity() {
	m_Position.m_X = 400.0f;
	m_Position.m_Y = 500.0f;
}

CUnit::~CUnit() {}

void CUnit::Render() {

	m_Width = static_cast<float>(m_pCTexture->m_Info.bmWidth);
	m_Height = static_cast<float>(m_pCTexture->m_Info.bmHeight);

	m_DisplayX = m_Position.m_X - m_Width * m_AnchorX;
	m_DisplayY = m_Position.m_Y - m_Height * m_AnchorY;

	m_pEngine->DrawTexture(m_DisplayX, m_DisplayY, m_pCTexture);
}

void CUnit::SetTexture(CTexture* pCTexture) {
	m_pCTexture = pCTexture;
}

void CUnit::SetEngine(CAPIEngine* pEngine) {
	m_pEngine = pEngine;
}

void CUnit::SetAnchors(float anchorX, float anchorY) {
	m_AnchorX = anchorX;
	m_AnchorY = anchorY;
}

void CUnit::Update() {
	//m_Position = m_Position + m_Velocity; 

	m_Position = m_Position + m_Velocity* m_pEngine->m_DeltaTime;

}
