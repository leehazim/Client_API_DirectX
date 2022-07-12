#include "CRef.h"

void CRef::AddRef() {
	m_Ref++;
}

int CRef::Release() {
	m_Ref--;

	if (m_Ref == 0) {
		delete this;
		return 0;
	}

	return m_Ref;
}