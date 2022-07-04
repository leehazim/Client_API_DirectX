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

	void SetPosition(SVector2D position);
	SVector2D GetPosition() const;

	SVector2D GetRect() const;
	SVector2D GetAnchors() const;

protected:
	SVector2D m_Position;

	float m_Width = 0.0f;
	float m_Height = 0.0f;

	float m_AnchorX = 0.5f;
	float m_AnchorY = 0.5f;
};
