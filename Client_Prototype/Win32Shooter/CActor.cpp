#include "CActor.h"
#include "CBullet.h"
#include "CAPIEngine.h"

CObject* CActor::Clone() {
	return new CActor(*this);
}

CActor::CActor()
	: CUnit(), m_CurIndexBullet(0) {}

CActor::CActor(const CActor& tActor)
	: CUnit(tActor), m_CurIndexBullet(0) {
	*this = tActor;
}

CActor::~CActor() {}

void CActor::DoFire(std::vector<CBullet*>& bullets) {

	bullets[m_CurIndexBullet]->SetPosition(SVector2D(m_Position.m_X, m_Position.m_Y));
	bullets[m_CurIndexBullet]->SetVelocity(SVector2D(0.0f, -1.0f) * 200.0f);
	bullets[m_CurIndexBullet]->SetIsActive(true);

	if (m_CurIndexBullet < bullets.size() - 1) {
		m_CurIndexBullet++;
	}
	else {
		m_CurIndexBullet = 0;
	}
}

void CActor::Update(float deltaTime){
	CUnit::Update(deltaTime);
	const float half = 0.5f;
	const float zero = 0.0f;

	if (this->m_Position.m_X - this->m_Width * half < zero)	{
		this->m_Position.m_X = zero + this->m_Width * half;
	}

	if (this->m_Position.m_X + this->m_Width * half > m_pEngine->GetClientWidth()){
		this->m_Position.m_X = m_pEngine->GetClientWidth() - this->m_Width * half;
	}
}
