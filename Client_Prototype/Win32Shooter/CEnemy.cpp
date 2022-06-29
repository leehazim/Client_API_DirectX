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
		SetVelocity(SVector2D(+1.0f, 0.0f) * GetVelocity().size());
		/*SetVelocity(GetVelocity() * reDirection);*/
	}
	if (m_Position.m_X + m_Width * half > m_pEngine->GetClientWidth()) {
		SetVelocity(SVector2D(-1.0f, 0.0f) * GetVelocity().size());
		/*SetVelocity(GetVelocity() * reDirection);*/
	}
}

void CEnemy::DoFire(std::vector<CBullet*>& bullets) {
	float zero = 0.0f;
	float direction = 1.0f;
	float velocity = 200.0f;
	int firstIndex = 0;
	int maxIndex = bullets.size() - 1;

	wchar_t szTemp[64] = { 0 };
	wsprintf(szTemp, L"NormalFire");
	OutputDebugString(szTemp);

	bullets[m_CurrentIndex]->SetPosition(m_Position);
	bullets[m_CurrentIndex]->SetVelocity(SVector2D(zero, direction) * velocity);
	bullets[m_CurrentIndex]->SetIsActive(true);
	if (m_CurrentIndex < maxIndex) {
		m_CurrentIndex++;
	}
	else {
		m_CurrentIndex = firstIndex;
	}
}

void CEnemy::DoFireAimed(std::vector<CBullet*>& bullets, CObject* pObject) {
	float zero = 0.0f;
	float velocity = 200.0f;
	SVector2D startPoint = m_Position;
	SVector2D targetPoint = pObject->GetPosition();
	SVector2D direction = (targetPoint - startPoint).nomalization();

	bullets[m_CurrentIndex]->SetPosition(startPoint);
	bullets[m_CurrentIndex]->SetVelocity(direction * velocity);
	bullets[m_CurrentIndex]->SetIsActive(true);

	wchar_t szTemp[64] = { 0 };
	wsprintf(szTemp, L"AImedFire");
	OutputDebugString(szTemp);

	int maxIndex = bullets.size() - 1;
	if (m_CurrentIndex < maxIndex) {
		m_CurrentIndex++;
	}
	else {
		int firstIndex = 0;
		m_CurrentIndex = firstIndex;
	}
}
