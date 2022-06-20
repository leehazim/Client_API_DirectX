#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CObject 
	: public CRef {

public:
	CObject();
	virtual ~CObject();

public:
	SVector2D m_Position;
};
