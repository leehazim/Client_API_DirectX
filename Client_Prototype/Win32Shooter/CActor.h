#pragma once

#include "CUnit.h"
#include <vector>
class CBullet;
class CActor
	: public CUnit {
public:
	CActor();
	CActor(const CActor& other);
	virtual ~CActor();

public:
	virtual CObject* Clone() override;
	virtual void Update(float deltaTime) override;

	void DoFire(std::vector<CBullet*>& bullets);

private:
	int m_CurIndexBullet;
};

