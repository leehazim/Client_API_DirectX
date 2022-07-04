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
