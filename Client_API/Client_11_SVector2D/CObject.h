#pragma once
#include "SVector2D.h"

class CObject {
public:
	CObject();
	virtual ~CObject();

	void AddRef();
	int Release();

public:
	int m_Ref;
	
	SVector2D m_Position;
};

// COM��ü�� ������� �̷� ����ΰ� ������.....