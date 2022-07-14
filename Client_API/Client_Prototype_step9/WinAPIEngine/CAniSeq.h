#pragma once
// �ִϸ��̼��� ���� ��������Ʈ���� ���� �ε��� ������ �� �� �ֵ��� ���͸� ����Ѵ�.
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
		// �ؽ�ó�� �����ڿ�, ���� ������ �ʿ䰡 ����.
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