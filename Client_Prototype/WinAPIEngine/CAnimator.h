#pragma once
#include <unordered_map>
#include <string>
#include <Windows.h>

class CAPIEngine;
class CAniSeq;

class CAnimator {
public:
	CAnimator();
	CAnimator(const CAnimator& other);
	void operator=(const CAnimator& other);
	~CAnimator();

	void SetId(std::string id) { m_Id = id; }
	bool Create(CAPIEngine* pEngine) { 
		m_pEngine = pEngine;
		return true;
	}
	void Destroy() {}

	void UpdateAnimation(float deltaTime);
	void Render(CAPIEngine* pEngine, float x, float y);
	bool AddAniSeq(const std::string& name,
				   float timeInterval, int totalFrameCount, LPCWSTR pFileName);

private:
	std::unordered_map<std::string, CAniSeq*> m_AniSeqs;
	std::string m_Id = "";

	CAniSeq* m_pCurAniSeq = nullptr;
	std::string m_StrKeyCurAniSeq;

	CAPIEngine* m_pEngine = nullptr;
};
	
