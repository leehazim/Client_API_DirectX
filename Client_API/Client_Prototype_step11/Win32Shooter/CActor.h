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
	

	// ��� �޾Ƽ� ������ �� �ִ� �浹 ������ü�� ����
	virtual void OnEnterCollision(CCollider* other) override {
		if (other->GetOnwerObject()->GetTag() == "tagEnemyBullet") {
			this->SetIsActive(false);
			static_cast<CUnit*>(other->GetOnwerObject())->SetIsActive(false);
		}
	}

private:
	int m_CurIndexBullet;
};

