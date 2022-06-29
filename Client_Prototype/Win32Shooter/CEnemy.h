#pragma once
#include "CUnit.h"
#include <vector>

class CBullet;

class CEnemy 
	: public CUnit{
public:
	CEnemy();
	CEnemy(const CEnemy& other);
	virtual ~CEnemy();

public:
	virtual CObject* Clone() override;
	virtual void Update(float deltaTime) override;
	
	void DoFire(std::vector<CBullet*>&bullets);

	void DoFireAimed(std::vector<CBullet*>& bullets, CObject* pObject);

public:
	float m_TimeTick = 0.0f;

private:
	int m_CurrentIndex = 0;

};

