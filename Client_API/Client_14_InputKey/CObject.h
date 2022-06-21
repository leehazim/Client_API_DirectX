#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CObject 
	: public CRef {

public:
	CObject();
	virtual ~CObject();

protected:
	SVector2D m_Position;
};
