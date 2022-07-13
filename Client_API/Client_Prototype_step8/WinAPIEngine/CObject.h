#pragma once
#include "SVector2D.h"
#include "CRef.h"
#include <string>

class CCollider;

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

	void SetTag(const std::string& tag) { m_Tag = tag; }
	std::string GetTag() const { return m_Tag; }

	virtual void OnEnterCollision(CCollider* other) = 0;
	virtual void OnStayCollision(CCollider* other) = 0;
	virtual void OnEndCollision(CCollider* other) = 0;

protected:
	SVector2D m_Position;

	float m_Width = 0.0f;
	float m_Height = 0.0f;

	float m_AnchorX = 0.5f;
	float m_AnchorY = 0.5f;

	std::string m_Tag = "";
};
