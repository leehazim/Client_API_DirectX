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
	

	// 상속 받아서 동작할 수 있는 충돌 관리객체로 관리
	virtual void OnEnterCollision(CCollider* other) override {
		if (other->GetOnwerObject()->GetTag() == "tagEnemyBullet") {
			this->SetIsActive(false);
			static_cast<CUnit*>(other->GetOnwerObject())->SetIsActive(false);
		}
	}

private:
	int m_CurIndexBullet;
};

