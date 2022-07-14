#pragma once
// 애니메이션을 위한 스프라이트들을 빠른 인덱스 접근을 할 수 있도록 벡터를 사용한다.
#include <vector>
#include <string>

class CTexture;
enum ANI_INFO {
	LOOP = 0,
	ONCE,
};

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
	void SetId(std::string name) { m_Id = name; }

	float GetTimeInterval() const { return m_TimeInterval; }
	void SetTimeInterval(float time) { m_TimeInterval = time; }
	
	float GetAniTime() const { return m_AnimTime; }
	void SetAniTime(float time) { m_AnimTime = time; }

	int GetTotalFrameCount() const { return m_TotalFrameCount; }
	void SetTotalFrameCount(int count) { m_TotalFrameCount = count; }

	CTexture* GetTexture(int idx) { return m_Textures[idx]; }
	void SetTextures(CTexture* texture) { m_Textures.push_back(texture); }
	
	int GetCurIndex() const { return m_CurrentFrameIndex; }
	void SetCurIndex(int idx) { m_CurrentFrameIndex = idx; }

	ANI_INFO GetIsLoop() const { return m_IsLoop; }
	void SetIsLoop(ANI_INFO value) { m_IsLoop = value; }

private:
	std::string m_Id;
	std::vector<CTexture*> m_Textures;

	float m_TimeInterval = 0.1f;	// AnimDeley
	float m_AnimTime = 0.0f;		// AnimTime
	
	int m_TotalFrameCount = 0;		// Sprite Count
	int m_CurrentFrameIndex = 0;	// Now Sprite Index
	
	ANI_INFO m_IsLoop = ANI_INFO::LOOP;
};