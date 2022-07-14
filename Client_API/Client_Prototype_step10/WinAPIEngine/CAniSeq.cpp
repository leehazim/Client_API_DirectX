#include "CAniSeq.h"

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
