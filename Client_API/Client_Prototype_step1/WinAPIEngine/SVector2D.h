#pragma once
struct SVector2D {
	float m_X = 0.0f;
	float m_Y = 0.0f;

	SVector2D() : m_X(0.0f), m_Y(0.0f) {}
	SVector2D(float aX, float aY) : m_X(aX), m_Y(aY) {}
	~SVector2D() {}

	SVector2D(const SVector2D& other) {
		m_X = other.m_X;
		m_Y = other.m_Y;
	}

	// ∫§≈Õ¿« ø¨ªÍ
	SVector2D& operator =(const SVector2D& other) {
		m_X = other.m_X;
		m_Y = other.m_Y;

		return *this;
	}

	SVector2D& operator +(const SVector2D& a) {
		m_X = m_X + a.m_X;
		m_Y =  m_Y + a.m_Y;

		return *this;
	}

	SVector2D& operator +=(const SVector2D& a) {
		m_X += a.m_X;
		m_Y += a.m_Y;
		return *this;
	}

	SVector2D& operator -(const SVector2D& a) {
		m_X = m_X - a.m_X;
		m_Y = m_Y - a.m_Y;
		return *this;
	}

	SVector2D& operator -=(const SVector2D& a) {
		m_X -= a.m_X;
		m_Y -= a.m_Y;
		return *this;
	}

	SVector2D& operator *(const float& a) {
		m_X = m_X * a;
		m_Y = m_Y * a;
		return *this;
	}
	
	SVector2D& operator *=(const float& a) {
		m_X *= a;
		m_Y *= a;
		return *this;
	}
};
