#pragma once
class CRef {
public:
	CRef()  
		: m_Ref(0) {}
	virtual ~CRef() {}

	void AddRef();
	int Release();

public:
	int m_Ref;
};

