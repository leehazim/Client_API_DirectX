#pragma once
class CRef {
public:
	CRef()  
		: m_Ref(0) {}
	virtual ~CRef() {}

	void AddRef();
	int Release();

protected:
	int m_Ref;
};

