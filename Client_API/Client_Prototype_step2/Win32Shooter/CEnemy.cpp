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
	float zero = 0.0f;
	float reDirection = -1.0f;

	if (m_Position.m_X - m_Width * half < zero) {
		SetVelocity(GetVelocity() * reDirection);
	}
	if (m_Position.m_X + m_Width * half > m_pEngine->GetClientWidth()) {
		SetVelocity(GetVelocity() * reDirection);
	}
}

void CEnemy::DoFire(std::vector<CBullet*>& bullets) {
	float zero = 0.0f;
	float direction = 1.0f;
	float velocity = 200.0f;
	int firstIndex = 0;
	int maxIndex = bullets.size() - 1;

	bullets[m_CurrentIndex]->SetPosition(SVector2D(m_Position.m_X, m_Position.m_Y));
	bullets[m_CurrentIndex]->SetVelocity(SVector2D(zero, direction) * velocity);
	bullets[m_CurrentIndex]->SetIsActive(true);
	if (m_CurrentIndex < maxIndex) {
		m_CurrentIndex++;
	}
	else {
		m_CurrentIndex = firstIndex;
	}
}
