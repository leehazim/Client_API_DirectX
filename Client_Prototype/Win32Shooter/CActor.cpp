#include "CActor.h"
#include "CBullet.h"

CObject* CActor::Clone() {
	return new CActor(*this);
}

CActor::CActor()
	: CUnit(), m_CurIndexBullet(0) {}

CActor::CActor(const CActor& tActor)
	: CUnit(tActor), m_CurIndexBullet(0) {
	m_Position = tActor.m_Position;

	m_pEngine = tActor.m_pEngine;
	m_IsActive = tActor.m_IsActive;

	m_Velocity = tActor.m_Velocity;

	//CUnit

	m_Radius = tActor.m_Radius;

	m_AnchorX = tActor.m_AnchorX;
	m_AnchorY = tActor.m_AnchorY;

	m_DisplayX = tActor.m_DisplayX;
	m_DisplayY = tActor.m_DisplayY;

	m_Width = tActor.m_Width;
	m_Height = tActor.m_Height;


	//shallow copy
	m_pCTexture = tActor.m_pCTexture;
}

//CActor& CActor::operator=(const CActor& other) {
//	*this = other;
//	return *this;
//}

CActor::~CActor() {}

void CActor::DoFire(std::vector<CBullet*>& bullets) {
	// 탄환 발사 알고리즘
	/*
	* 발사 시작 지점 정하기
	* 발사 속도 지정
	* 탄환 활성화
	*/
	bullets[m_CurIndexBullet]->SetPosition(SVector2D(this->m_Position.m_X, this->m_Position.m_Y));
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

	if (this->m_Position.m_X - this->m_Width * 0.5f < 0.0f)
	{
		this->m_Position.m_X = 0.0f + this->m_Width * 0.5f;
	}

	if (this->m_Position.m_X + this->m_Width * 0.5f > 800.0f)
	{
		this->m_Position.m_X = 800.0f - this->m_Width * 0.5f;
	}
}
