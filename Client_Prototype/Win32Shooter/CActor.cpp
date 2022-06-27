#include "CActor.h"
#include "CBullet.h"

CObject* CActor::Clone() {
	return new CActor(*this);
}

CActor::CActor()
	: CUnit() {}

CActor::CActor(const CActor& other) 
	: CUnit(other) {
	
}

CActor& CActor::operator=(const CActor& other) {
	*this = other;
	return *this;
}

CActor::~CActor() {}

void CActor::DoFire(std::vector<CBullet*>& bullets) {
	// źȯ �߻� �˰���
	/*
	* �߻� ���� ���� ���ϱ�
	* �߻� �ӵ� ����
	* źȯ Ȱ��ȭ
	*/
	bullets[m_CurIndexBullet]->SetPosition(this->GetPosition());
	bullets[m_CurIndexBullet]->SetVelocity(SVector2D(0.0f, -200.0f));
	bullets[m_CurIndexBullet]->SetIsActive(true);

	if (m_CurIndexBullet < bullets.size() - 1) {
		m_CurIndexBullet++;
	}
	else {
		m_CurIndexBullet = 0;
	}
}
