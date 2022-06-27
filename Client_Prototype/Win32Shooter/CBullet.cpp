#include "CBullet.h"

CBullet::CBullet() 
	: CUnit() {}

CBullet::CBullet(const CBullet& tBullet) 
	: CUnit(tBullet) {
	m_Position = tBullet.m_Position;

	//ryu winAPIShootor_step_0
	m_pEngine = tBullet.m_pEngine;
	m_IsActive = tBullet.m_IsActive;



	m_Velocity = tBullet.m_Velocity;

	//CUnit

	m_Radius = tBullet.m_Radius;

	m_AnchorX = tBullet.m_AnchorX;
	m_AnchorY = tBullet.m_AnchorY;

	m_DisplayX = tBullet.m_DisplayX;
	m_DisplayY = tBullet.m_DisplayY;

	m_Width = tBullet.m_Width;
	m_Height = tBullet.m_Height;


	//shallow copy
	m_pCTexture = tBullet.m_pCTexture;

}

CBullet::~CBullet() {
}
