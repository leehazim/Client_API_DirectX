#include "CCollider.h"
#include "CObject.h"

CCollider::CCollider() :
	m_Position(),
	m_Width(0),
	m_Height(0) {}

CCollider::CCollider(const CCollider& collider) {
	m_Position = collider.m_Position;

	m_Width = collider.m_Width;
	m_Height = collider.m_Height;

	m_pObject = collider.m_pObject;
}

void CCollider::operator=(const CCollider& collider) {
	m_Position = collider.m_Position;

	m_Width = collider.m_Width;
	m_Height = collider.m_Height;

	m_pObject = collider.m_pObject;
}

CCollider::~CCollider() {}

bool CCollider::DoCollisionby(CObject* other) {
	bool result = false;
	result = DoCollisionAABB(other, 1);
	return result;
}

bool CCollider::DoCollision(CCollider* colliderOther,int) {
	bool result = false;
	result = DoCollisionAABB(colliderOther);
	return result;
}

void CCollider::Create(SVector2D position, float width, float height) {
	m_Position = position;

	m_Width = width;
	m_Height = height;
}

void CCollider::Update() {
	m_Position = m_pObject->GetPosition();
}

void CCollider::SetPosition(SVector2D position) {
	m_Position = position;
}

void CCollider::SetSize(float width, float height) {
	m_Width = width;
	m_Height = height;
}

void CCollider::SetOnwerObject(CObject* pObject) {
	m_pObject = pObject;
}

CObject* CCollider::GetOnwerObject() const {
	return m_pObject;
}

bool CCollider::DoCollisionAABB(CCollider* other) {
	SVector2D anchors = m_pObject->GetAnchors();
	float leftX = m_Position.m_X - m_Width * anchors.m_X;
	float rightX = m_Position.m_X - m_Width * anchors.m_X + m_Width;
	float topY = m_Position.m_Y - m_Height * anchors.m_Y;
	float bottomY = m_Position.m_Y - m_Height * anchors.m_Y + m_Height;

	SVector2D otherPos = other->GetOnwerObject()->GetPosition();
	SVector2D otherAnchor = other->GetOnwerObject()->GetAnchors();
	SVector2D otherRect = other->GetOnwerObject()->GetRect();
	float leftX_other =		otherPos.m_X - otherRect.m_X * otherAnchor.m_X;
	float rightX_other =	otherPos.m_X - otherRect.m_X * otherAnchor.m_X + otherRect.m_X;
	float topY_other =		otherPos.m_Y - otherRect.m_Y * otherAnchor.m_Y;
	float bottomY_other =	otherPos.m_Y - otherRect.m_Y * otherAnchor.m_Y + otherRect.m_Y;

	if (rightX < leftX_other) 		return false;
	if (leftX > rightX_other) 		return false;
	if (bottomY < topY_other)		return false;
	if (topY > bottomY_other)		return false;
	return true;
}

bool CCollider::DoCollisionAABB(CObject* other, int n) {
	SVector2D anchors = m_pObject->GetAnchors();
	float leftX = m_Position.m_X - m_Width * anchors.m_X;
	float rightX = m_Position.m_X - m_Width * anchors.m_X + m_Width;
	float topY = m_Position.m_Y - m_Height * anchors.m_Y;
	float bottomY = m_Position.m_Y - m_Height * anchors.m_Y + m_Height;

	SVector2D otherPos = other->GetPosition();
	SVector2D otherAnchor = other->GetAnchors();
	SVector2D otherRect = other->GetRect();
	float leftX_other = otherPos.m_X - otherRect.m_X * otherAnchor.m_X;
	float rightX_other = otherPos.m_X - otherRect.m_X * otherAnchor.m_X + otherRect.m_X;
	float topY_other = otherPos.m_Y - otherRect.m_Y * otherAnchor.m_Y;
	float bottomY_other = otherPos.m_Y - otherRect.m_Y * otherAnchor.m_Y + otherRect.m_Y;

	if (rightX < leftX_other) 		return false;
	if (leftX > rightX_other) 		return false;
	if (bottomY < topY_other)		return false;
	if (topY > bottomY_other)		return false;
	return true;
}
