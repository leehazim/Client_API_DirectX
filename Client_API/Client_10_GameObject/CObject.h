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

