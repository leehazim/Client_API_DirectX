#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CObject 
	: public CRef {

public:
	CObject();
	virtual ~CObject();

public:
	virtual CObject* Clone() = 0;

protected:
	SVector2D m_Position;
};
