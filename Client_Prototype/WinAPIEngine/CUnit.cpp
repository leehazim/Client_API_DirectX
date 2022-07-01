#include "CUnit.h"
#include "CAPIEngine.h"
#include "CTexture.h"

CUnit::CUnit() :
	CObject(),
	m_Radius(30.0f),
	m_pCTexture(nullptr),
	m_pEngine(nullptr),
	m_IsActive(false),
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

	m_IsActive = other.m_IsActive;
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

	m_IsActive = other.m_IsActive;
	return *this;
}
void CUnit::Create(CAPIEngine* pEngine) {
	SetEngine(pEngine);
}

void CUnit::Destroy() {

}

void CUnit::Update(float deltaTime) {
	if (m_IsActive) {
		m_Position = m_Position + m_Velocity * deltaTime;
	}
}

void CUnit::Render() {
	if (this->GetIsActive()) {
		m_DisplayX = m_Position.m_X - m_Width * m_AnchorX;
		m_DisplayY = m_Position.m_Y - m_Height * m_AnchorY;

		m_pEngine->DrawTexture(m_DisplayX, m_DisplayY, m_pCTexture);
		/*m_pEngine->DrawCircle(m_Position.m_X, m_Position.m_Y, m_Radius);*/
	}
}

void CUnit::SetTexture(CTexture* pCTexture) {
	m_pCTexture = pCTexture;

	m_Width = static_cast<float>(m_pCTexture->m_Info.bmWidth);
	m_Height = static_cast<float>(m_pCTexture->m_Info.bmHeight);
}

void CUnit::SetEngine(CAPIEngine* pEngine) {
	m_pEngine = pEngine;
}

void CUnit::SetAnchors(float anchorX, float anchorY) {
	m_AnchorX = anchorX;
	m_AnchorY = anchorY;
}

SVector2D CUnit::GetAnchors() const {
	return SVector2D(m_AnchorX, m_AnchorY);
}

SVector2D CUnit::GetRect() const {
	return SVector2D(m_Width, m_Height);
}

void CUnit::SetVelocity(SVector2D speed) {
	m_Velocity = speed;
}

SVector2D CUnit::GetVelocity() const {
	return m_Velocity;
}

void CUnit::SetIsActive(bool isActive) {
	m_IsActive = isActive;
}

bool CUnit::GetIsActive() const {
	return m_IsActive;
}

float CUnit::GetRadius() const {
	return m_Radius;
}

void CUnit::SetRadius(float radius) {
	m_Radius = radius;
}

bool CUnit::IsTrigger(const CUnit& other) const {
	// AABB를 위한 변수
	/*float leftX = 0.f;
	float rightX = 0.f;
	float topY = 0.f;
	float bottomY = 0.f;

	float leftX_other = 0.f;
	float rightX_other = 0.f;
	float topY_other = 0.f;
	float bottomY_other = 0.f;*/
	
	float leftX = m_Position.m_X - m_Width * m_AnchorX;
	float rightX = m_Position.m_X - m_Width * m_AnchorX +m_Width;
	float topY = m_Position.m_Y - m_Height * m_AnchorY;
	float bottomY = m_Position.m_Y - m_Height * m_AnchorY + m_Height;
	
	SVector2D otherPos = other.GetPosition();
	SVector2D otherAnchor = other.GetAnchors();
	SVector2D otherRect = other.GetRect();
	float leftX_other = otherPos.m_X - otherRect.m_X * otherAnchor.m_X;
	float rightX_other = otherPos.m_X - otherRect.m_X * otherAnchor.m_X + otherRect.m_X;
	float topY_other = otherPos.m_Y - otherRect.m_Y * otherAnchor.m_Y;
	float bottomY_other = otherPos.m_Y - otherRect.m_Y * otherAnchor.m_Y + otherRect.m_Y;

	if (rightX < leftX_other) 		return false;
	if (leftX > rightX_other) 		return false;
	if (bottomY < topY_other)		return false;
	if (topY > bottomY_other)		return false;
	return true;
}

