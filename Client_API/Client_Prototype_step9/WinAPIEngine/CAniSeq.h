#pragma once
// 애니메이션을 위한 스프라이트들을 빠른 인덱스 접근을 할 수 있도록 벡터를 사용한다.
#include <vector>
#include <string>

class CTexture;

class CAniSeq {
public:
	CAniSeq() :
		m_Id(""),
		m_AnimTime(0.0f),
		m_TimeInterval(0.1f),
		m_CurrentFrameIndex(0),
		m_TotalFrameCount(0) { }
	CAniSeq(const CAniSeq& other) {
		*this = other;
		// 텍스처는 공유자원, 깊은 복사의 필요가 없다.
	}
	~CAniSeq() { m_Textures.clear(); }

	void Update(float deltaTime);

	std::string GetId() const { return m_Id; }

	void SetTimeInterval(float time) { m_TimeInterval = time; }
	void SetAniTime(float time) { m_AnimTime = time; }

	void SetTotalFrameCount(int count) { m_TotalFrameCount = count; }
	void SetTextures(CTexture* texture) { m_Textures.push_back(texture); }

	CTexture* GetTexture(int idx) { return m_Textures[idx]; }
	int GetCurIndex() const { return m_CurrentFrameIndex; }

private:
	std::string m_Id;
	std::vector<CTexture*> m_Textures;

	float m_TimeInterval = 0.1f; 
	float m_AnimTime = 0.0f;
	
	int m_TotalFrameCount = 0;
	int m_CurrentFrameIndex = 0;
};