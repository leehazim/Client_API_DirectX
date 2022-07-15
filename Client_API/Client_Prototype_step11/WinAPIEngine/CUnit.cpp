#include "CUnit.h"
#include "CAPIEngine.h"
#include "CTexture.h"
#include "CAnimator.h"

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

CUnit::~CUnit() {
	SAFE_DELETE(m_pCollider);
}

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
	m_Tag = other.m_Tag;
	
	// 깊은 복사
	m_pCollider = new CCollider();
	*m_pCollider = *other.m_pCollider;
	m_pCollider->SetOnwerObject(this);

	if (other.m_pAnimator != nullptr) {
		m_pAnimator = new CAnimator();
		(*m_pAnimator) = (*other.m_pAnimator);
		m_pAnimator->SetOwnerObject(this);
	}
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

	// 텍스처와 엔진은 모두 하나의 자원을 공유하는 상태여서
	// 얕은 복사를 해도 된다.
	// 직접 해제할 일과 세팅할 일은 없다.
	m_pCTexture = other.m_pCTexture;
	m_pEngine = other.m_pEngine;

	m_IsActive = other.m_IsActive;
	m_Tag = other.m_Tag;

	// 하지만 직접 값을 대입하고 해제도 하는 콜라이더는 모든 유닛이 따로 가지고있다.
	m_pCollider = new CCollider();
	*m_pCollider = *other.m_pCollider;
	m_pCollider->SetOnwerObject(this);

	if (other.m_pAnimator != nullptr) {
		m_pAnimator = new CAnimator();
		*m_pAnimator = *other.m_pAnimator;
		m_pAnimator->SetOwnerObject(this);
	}
	return *this;
}
void CUnit::Create(CAPIEngine* pEngine) {
	SetEngine(pEngine);

	m_pCollider = new CCollider();
	m_pCollider->Create(this->GetPosition(), 100.f, 100.f);
	m_pCollider->SetOnwerObject(this);
}

void CUnit::Destroy() {
	SAFE_DELETE(m_pCollider);
}

void CUnit::Update(float deltaTime) {
	if (m_IsActive) {
		m_Position = m_Position + m_Velocity * deltaTime;

		m_pCollider->Update();
	}
}

void CUnit::Render() {
	if (this->GetIsActive()) {
		m_DisplayX = m_Position.m_X - m_Width * m_AnchorX;
		m_DisplayY = m_Position.m_Y - m_Height * m_AnchorY;

		if (m_pAnimator != nullptr) {
			m_pAnimator->UpdateAnimation(m_pEngine->m_DeltaTime);
			m_pAnimator->Render(m_pEngine, m_DisplayX, m_DisplayY);
		}
		else {
			m_pEngine->DrawTexture(m_DisplayX, m_DisplayY, m_pCTexture);
		}
		/*m_pEngine->DrawCircle(m_Position.m_X, m_Position.m_Y, m_Radius);*/
	}
}

void CUnit::SetTexture(CTexture* pCTexture) {
	m_pCTexture = pCTexture;

	m_Width = static_cast<float>(m_pCTexture->m_Info.bmWidth);
	m_Height = static_cast<float>(m_pCTexture->m_Info.bmHeight);
	m_pCollider->SetSize(m_Width, m_Height);
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

void CUnit::SetIsActive(bool isActive) {
	m_IsActive = isActive;
}

bool CUnit::GetIsActive() const {
	return m_IsActive;
}

float CUnit::GetRadius() const {
	return m_Radius;
}

CCollider* CUnit::GetCollider() const {
	return m_pCollider;
}

CAnimator* CUnit::CreateAnimator(const std::string id, CAPIEngine* pEngine) {
	m_pAnimator = new CAnimator();
	m_pAnimator->SetId(id);
	m_pAnimator->Create(pEngine);
	if (!m_pAnimator) return nullptr;
	return m_pAnimator;
}

void CUnit::DestroyAnimator() {
	if (m_pAnimator) {
		m_pAnimator->Destroy();
	}
	SAFE_DELETE(m_pAnimator);
}

void CUnit::SetRadius(float radius) {
	m_Radius = radius;
}


