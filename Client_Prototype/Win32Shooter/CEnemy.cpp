#include "CEnemy.h"
#include "CBullet.h"
#include "CAPIEngine.h"

CEnemy::CEnemy() :
	CUnit() {
}

CEnemy::CEnemy(const CEnemy& other) :
	CUnit() {
	*this = other;
}

CEnemy::~CEnemy() {
}

CObject* CEnemy::Clone() {
	return new CEnemy(*this);
}

void CEnemy::Update(float deltaTime) {
	CUnit::Update(deltaTime);
	float half = 0.5f;
	if (m_Position.m_X - m_Width * half < 0.0f) {
		m_Velocity = m_Velocity * -1.0f;
	}
	if (m_Position.m_X + m_Width * half > m_pEngine->GetClientWidth()) {
		m_Velocity = m_Velocity * -1.0f;
	}
}

void CEnemy::DoFire(std::vector<CBullet*>& bullets) {
	bullets[m_CurrentIndex]->SetPosition(SVector2D(m_Position.m_X, m_Position.m_Y));
	bullets[m_CurrentIndex]->SetVelocity(SVector2D(0.0f, +1.0f) * 200.0f);
	bullets[m_CurrentIndex]->SetIsActive(true);
	if (m_CurrentIndex < bullets.size() - 1) {
		m_CurrentIndex++;
	}
	else {
		m_CurrentIndex = 0;
	}
}
