#pragma once
#include <unordered_map>
#include <string>
#include <Windows.h>
#include "CAniSeq.h"

class CAPIEngine;
class CAniSeq;
class CObject;

class CAnimator {
public:
	CAnimator();
	CAnimator(const CAnimator& other);
	void operator=(const CAnimator& other);
	~CAnimator();

	void SetId(std::string id) { m_Id = id; }
	void Destroy() {}
	bool Create(CAPIEngine* pEngine) { 
		m_pEngine = pEngine;
		return true;
	}

	void UpdateAnimation(float deltaTime);
	void Render(CAPIEngine* pEngine, float x, float y);
	bool AddAniSeq(const std::string& name,
				   float timeInterval, int totalFrameCount, LPCWSTR pFileName, ANI_INFO isLoopOption = ANI_INFO::LOOP);

	void SetOwnerObject(CObject* onwer) { m_pOnwerObject = onwer; }
	CObject* GetOnwerObject() const { return m_pOnwerObject; }

	std::string GetKey() { return m_StrKeyCurAniSeq; }
	void SetKey(std::string key) { m_StrKeyCurAniSeq = key; }

	std::string GetPrevKey() const { return m_StrKeyPrevAniSeq; }
	void SetPrevKey(std::string key) { m_StrKeyPrevAniSeq = key; }

	CAniSeq* GetAniSeq() const { return m_pCurAniSeq; }

private:
	std::unordered_map<std::string, CAniSeq*> m_AniSeqs;
	std::string m_Id = "";

	CAniSeq* m_pCurAniSeq = nullptr;
	std::string m_StrKeyCurAniSeq;
	std::string m_StrKeyPrevAniSeq;

	CAPIEngine* m_pEngine = nullptr;
	CObject* m_pOnwerObject = nullptr;
};
	
