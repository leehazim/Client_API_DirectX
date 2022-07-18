#include "CAniSeq.h"
#include "CTexture.h"

void CAniSeq::Update(float deltaTime) {
	if (m_AnimTime >= m_TimeInterval) {
		if (m_CurrentFrameIndex < m_TotalFrameCount - 1) {
			m_CurrentFrameIndex = m_CurrentFrameIndex + 1;
		}
		else {
			m_CurrentFrameIndex = 0;
		}
		m_AnimTime = 0.0f;
	}
	else {
		m_AnimTime = m_AnimTime + deltaTime;
	}
}

void CAniSeq::SetSpriteFrameWH(int row, int col) {
	/*m_Rows = row;
	m_Cols = col;
	m_SpriteOption = ANI_SO::SHEET_FILE;*/

	m_SpriteWidth = m_Textures[0]->m_Info.bmWidth / row;
	m_SpriteHeight = m_Textures[0]->m_Info.bmHeight / col;

}

