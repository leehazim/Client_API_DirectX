#pragma once
struct SVector2D {
	float m_X = 0.0f;
	float m_Y = 0.0f;

	SVector2D() :m_X(0.0f), m_Y(0.0f) {}
	SVector2D(float aX, float aY) : m_X(aX), m_Y(aY) {}
	~SVector2D() {}

	SVector2D(const SVector2D& other) {
		m_X = other.m_X;
		m_Y = other.m_Y;
	}

	// ?????? ????
	SVector2D& operator =(const SVector2D& other) {
		m_X = other.m_X;
		m_Y = other.m_Y;
	}

	SVector2D operator +(const SVector2D& a) {
		SVector2D result = {0.0f, 0.0f};
		result.m_X = m_X + a.m_X;
		result.m_Y = m_Y + a.m_Y;

		return result;
	}

	SVector2D operator -(const SVector2D& a) {
		SVector2D result = {0.0f, 0.0f};
		result.m_X = m_X - a.m_X;
		result.m_Y = m_X - a.m_Y;

		return result;
	}

	SVector2D operator *(const float scalar) {
		SVector2D result = { 0.0f, 0.0f };
		result.m_X = m_X * scalar;
		result.m_Y = m_Y * scalar;

		return result;
	}
};
