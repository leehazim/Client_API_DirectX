#include "CAnimator.h"
#include "CAniSeq.h"
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
	// ������ ���� ��������Ʈ �����͵��� �����ص� ������
	// ������ ��ü�� �����ؼ��� �ȵȴ�.
	// �ֱ� �������� ������ �� ������ �ʾƾ� �ϴ� ����� Object�� �Բ� ���ϴ� ���װ� �����.
	// �����ϰ� ���� ���� 
	*this = other;

	// ���� ���� �� ����
	m_AniSeqs.clear();
	std::unordered_map<std::string, CAniSeq*>::const_iterator it;
	for (it = other.m_AniSeqs.begin(); it != other.m_AniSeqs.end(); it++) {
		CAniSeq* pAniClip = new CAniSeq();
		*pAniClip = *it->second;
		m_AniSeqs.insert(make_pair(pAniClip->GetId(), pAniClip));
	}
}

void CAnimator::operator=(const CAnimator& other) {
	*this = other;

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
	this->m_StrKeyCurAniSeq = "ani_idle_actor";
	std::unordered_map<std::string, CAniSeq*>::iterator it = m_AniSeqs.find(m_StrKeyCurAniSeq);
	m_pCurAniSeq = it->second;

	m_pCurAniSeq->Update(deltaTime);
}

void CAnimator::Render(CAPIEngine* pEngine, float x, float y) {
	int index = m_pCurAniSeq->GetCurIndex();
	CTexture* pTex = m_pCurAniSeq->GetTexture(index);
	if (pTex) {
		m_pEngine->DrawTexture(x, y, pTex);
	}
}

bool CAnimator::AddAniSeq(const std::string& name, float timeInterval, int totalFrameCount, LPCWSTR pFileName) {
	CAniSeq* pClip = new CAniSeq();

	pClip->SetTimeInterval(timeInterval);
	pClip->SetTotalFrameCount(totalFrameCount);

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
