#include "CAnimator.h"
#include "macro.h"
#include "CTexture.h"
#include "CAPIEngine.h"

CAnimator::CAnimator() : 
	m_Id(""),
	m_pEngine(nullptr),
	m_pCurAniSeq(nullptr),
	m_StrKeyCurAniSeq("") {
	m_AniSeqs.clear();
}

CAnimator::CAnimator(const CAnimator& other) {
	// 시퀀스 안의 스프라이트 데이터들은 공유해도 되지만
	// 시퀀스 자체는 공유해서는 안된다.
	// 최근 시퀀스가 변했을 때 변하지 않아야 하는 복사된 Object도 함께 변하는 버그가 생긴다.
	// 간단하게 얕은 복사 
	/**this = other;*/
	m_Id = other.m_Id;
	m_pEngine = other.m_pEngine;
	m_pCurAniSeq = other.m_pCurAniSeq;
	m_StrKeyCurAniSeq = other.m_StrKeyCurAniSeq;
	m_StrKeyPrevAniSeq = other.m_StrKeyPrevAniSeq;
	m_pOnwerObject = other.m_pOnwerObject;

	// 얕은 복사 후 세팅
	m_AniSeqs.clear();
	std::unordered_map<std::string, CAniSeq*>::const_iterator it;
	for (it = other.m_AniSeqs.begin(); it != other.m_AniSeqs.end(); it++) {
		CAniSeq* pAniClip = new CAniSeq();
		*pAniClip = *it->second;
		m_AniSeqs.insert(make_pair(pAniClip->GetId(), pAniClip));
	}
}

void CAnimator::operator=(const CAnimator& other) {
	//*this = other;
	m_Id = other.m_Id;
	m_pEngine = other.m_pEngine;
	m_pCurAniSeq = other.m_pCurAniSeq;
	m_StrKeyCurAniSeq = other.m_StrKeyCurAniSeq;
	m_StrKeyPrevAniSeq = other.m_StrKeyPrevAniSeq;
	m_pOnwerObject = other.m_pOnwerObject;

	m_AniSeqs.clear();
	std::unordered_map<std::string, CAniSeq*>::const_iterator it;
	for (it = other.m_AniSeqs.begin(); it != other.m_AniSeqs.end(); it++) {
		CAniSeq* pAniClip = new CAniSeq();
		*pAniClip = *it->second;
		m_AniSeqs.insert(make_pair(pAniClip->GetId(), pAniClip));
	}
}

CAnimator::~CAnimator() {
	std::unordered_map<std::string, CAniSeq*>::iterator it;
	for (it = m_AniSeqs.begin(); it != m_AniSeqs.end(); it++) {
		SAFE_DELETE(it->second);
	}
	m_AniSeqs.clear();
}

void CAnimator::UpdateAnimation(float deltaTime) {
	/*this->m_StrKeyCurAniSeq = "ani_idle_actor";*/
	std::unordered_map<std::string, CAniSeq*>::iterator it = m_AniSeqs.find(m_StrKeyCurAniSeq);
	/*if (it == m_AniSeqs.end()) PostQuitMessage(0)*/;
	m_pCurAniSeq = it->second;

	m_pCurAniSeq->Update(deltaTime);
}

void CAnimator::Render(CAPIEngine* pEngine, float x, float y) {
	int index = m_pCurAniSeq->GetCurIndex();
	CTexture* pTex = m_pCurAniSeq->GetTexture(index);
	if (pTex) {
		m_pEngine->DrawTexture(x, y, pTex);
	}

	switch (m_pCurAniSeq->GetIsLoop()) {
	case ANI_INFO::LOOP:
	{
	}
	break;
	case ANI_INFO::ONCE:
	{
		if (m_pCurAniSeq->GetCurIndex() == m_pCurAniSeq->GetTotalFrameCount() - 1) {
			m_StrKeyCurAniSeq = m_StrKeyPrevAniSeq;
			m_pCurAniSeq->SetCurIndex(0);
			m_pCurAniSeq->SetAniTime(0.0f);
		}
	}
	break;
	}
}

bool CAnimator::AddAniSeq(const std::string& name, float timeInterval, int totalFrameCount, LPCWSTR pFileName, ANI_INFO isLoopOption) {
	CAniSeq* pClip = new CAniSeq();

	pClip->SetId(name);
	pClip->SetTimeInterval(timeInterval);
	pClip->SetTotalFrameCount(totalFrameCount);
	pClip->SetIsLoop(isLoopOption);

	for (int i = 0; i < totalFrameCount; i++) {
		CTexture* pTex = nullptr;
		pTex = new CTexture();

		WCHAR szTemp[256] = { 0 };
		wsprintf(szTemp, L"%s_%d.bmp", pFileName, i);

		pTex->LoadTexture(m_pEngine->GetHInst(), m_pEngine->GetHDC(), szTemp);
		pClip->SetTextures(pTex);
	}
	m_AniSeqs.insert(make_pair(name, pClip));
	return true;
}
