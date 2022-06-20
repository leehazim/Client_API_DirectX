#pragma once
class CObject {
public:
	CObject();
	virtual ~CObject();

public:
	int m_Ref;
	
	void AddRef();
	int Release();
};

// COM객체의 구현방식 이런 방식인거 같은데.....