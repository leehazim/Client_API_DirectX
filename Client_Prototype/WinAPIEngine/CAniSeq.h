#pragma once
// 애니메이션을 위한 스프라이트들을 빠른 인덱스 접근을 할 수 있도록 벡터를 사용한다.
#include <vector>
#include <string>

class CTexture;
enum ANI_INFO {
	LOOP = 0,
	ONCE,
};

enum ANI_SO {
	FRAME_FILE = 0,		// 프레임이 파일 하나하나에 할당된 경우
	SHEET_FILE,			// 프레임이 스프레트시트 방식으로 저장된 경우
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

	void SetSpriteFrameWH(int row = 1, int col = 1);

public:
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

	ANI_SO GetOption() const { return m_SpriteOption; }
	void SetOption(ANI_SO option) { m_SpriteOption = option; }

	int GetCols() const { return m_Cols; }
	void SetCols(int cols) { m_Cols = cols; }

	int GetRows() const { return m_Rows; }
	void SetRows(int rows) { m_Rows = rows; }
	
	int GetSpriteWidth() const { return m_SpriteWidth; }
	void SetSpriteWidth(int width) { m_SpriteWidth = width; }

	int GetSpriteHeight() const { return m_SpriteHeight; }
	void SetSpriteHeight(int height) { m_SpriteHeight = height; }

private:
	std::string m_Id;
	std::vector<CTexture*> m_Textures;

	float m_TimeInterval = 0.1f;	
	float m_AnimTime = 0.0f;		
	
	int m_TotalFrameCount = 0;		
	int m_CurrentFrameIndex = 0;	
	
	ANI_INFO m_IsLoop = ANI_INFO::LOOP;
	ANI_SO m_SpriteOption = ANI_SO::FRAME_FILE;

	// 스프라이트들의 너비 높이
	int m_SpriteWidth = 0;
	int m_SpriteHeight = 0;

	int m_Rows = 0;
	int m_Cols = 0;

	int m_FrameCol = 0;
};