#include "CActor.h"

CActor::CActor() 
	: CUnit() {}

CActor::CActor(const CActor& other) 
	: CUnit(other) {
	
}

CActor& CActor::operator=(const CActor& other) {
	*this = other;
	return *this;
}

CActor::~CActor() {}
