#pragma once
#include "CUnit.h"

class CBullet 
	: public CUnit{
public:
	CBullet();
	CBullet(const CBullet& other);
	virtual ~CBullet();

public:
	virtual CObject* Clone() override {
		return new CBullet(*this);
	}
};