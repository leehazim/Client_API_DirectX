#pragma once

#define SAFE_DELETE(__type) if( __type != nullptr) { delete __type ; __type = nullptr; }


#define SINGLETON_DECLEARE(p) public:\
	static p* GetInstance();\
	static void ReleaseInstance();\
private:\
	p();\
	~p();\
private:\
	static p* _Instance;