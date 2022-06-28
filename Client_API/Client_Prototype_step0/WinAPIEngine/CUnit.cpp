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

CUnit::CUnit(const CUnit& other) {
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
CUnit& CUnit::operator=(const CUnit& other) {
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
void CUnit::Create(CAPIEngine* pEngine) {
	SetEngine(pEngine);
}

void CUnit::Destroy() {

}

void CUnit::Update(float deltaTime) {
	m_Position += m_Velocity * deltaTime;
}

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

void CUnit::SetVelocity(SVector2D speed) {
	m_Velocity = speed;
}

SVector2D CUnit::GetVelocity() const {
	return m_Velocity;
}

void CUnit::SetPosition(SVector2D Position) {
	m_Position = Position;
}

SVector2D CUnit::GetPosition() const {
	return m_Position;
}
