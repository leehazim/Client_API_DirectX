#include "CObject.h"

CObject::CObject() 
	: m_Position(), CRef() {}

CObject::~CObject() {}

void CObject::SetPosition(SVector2D Position) {
	m_Position = Position;
}

SVector2D CObject::GetPosition() const {
	return m_Position;
}

SVector2D CObject::GetRect() const {
	return SVector2D(m_Width, m_Height);
}

SVector2D CObject::GetAnchors() const {
	return SVector2D(m_AnchorX, m_AnchorY);
}
