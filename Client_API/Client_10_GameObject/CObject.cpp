#include "CObject.h"

CObject::CObject() 
	: m_Ref(0) {}

CObject::~CObject() {}

void CObject::AddRef() {
	m_Ref++;
}

int CObject::Release() {
	m_Ref--;

	if (m_Ref == 0) {
		delete this;
		return 0 ;
	}

	return m_Ref;
}
