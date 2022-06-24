#include "CActor.h"

CActor::CActor() {}

CActor::CActor(const CActor& other) {
	m_pCTexture = other.m_pCTexture;
	m_pEngine = other.m_pEngine;
}

CActor& CActor::operator=(const CActor& other) {
	*this = other;
	return *this;
}

CActor::~CActor() {}
