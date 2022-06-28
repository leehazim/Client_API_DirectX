#pragma once

#include "CUnit.h"

class CActor
	: public CUnit {
public:

	virtual CObject* Clone()override {
		return new CActor(*this);
	}

	CActor();
	CActor(const CActor& other);
	CActor& operator =(const CActor& other);
	virtual ~CActor();

private:


};

