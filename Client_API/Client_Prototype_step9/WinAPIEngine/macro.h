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


#define SINGLETON_DEFINITION(p) p* p::_Instance = nullptr;\
p* p::GetInstance() {\
	if(_Instance == nullptr){\
		_Instance = new p();\
	}\
	return _Instance;\
}\
void p::ReleaseInstance() {\
	if (_Instance != nullptr) {\
		delete _Instance;\
	}\
}