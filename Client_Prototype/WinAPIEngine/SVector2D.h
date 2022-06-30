#pragma once
#include <cmath>
#include <cfloat>

struct SVector2D {
	float m_X = 0.0f;
	float m_Y = 0.0f;

	static const SVector2D ZERO;
	static const SVector2D LEFT;
	static const SVector2D RIGHT;
	static const SVector2D DOWN;
	static const SVector2D UP;

	SVector2D() : m_X(0.0f), m_Y(0.0f) {}
	SVector2D(float aX, float aY) : m_X(aX), m_Y(aY) {}
	~SVector2D() {}

	SVector2D(const SVector2D& other) {
		m_X = other.m_X;
		m_Y = other.m_Y;
	}

	// 기본 연산자 오버로딩
	const SVector2D operator +(const SVector2D& a) const {
		SVector2D result;
		result.m_X = m_X + a.m_X;
		result.m_Y = m_Y + a.m_Y;
		return result;
	}

	const SVector2D operator -(const SVector2D& a) const {
		SVector2D result;
		result.m_X = m_X - a.m_X;
		result.m_Y = m_Y - a.m_Y;
		return result;
	}

	const SVector2D operator *(const float& a) const {
		SVector2D result;
		result.m_X = m_X * a;
		result.m_Y = m_Y * a;
		return result;
	}

	// 스칼라 곱인데 편하게 하려고 역수 곱을 편하게 하기 위해서
	const SVector2D operator /(const float& a) const {
		SVector2D result;
		result.m_X = m_X / a;
		result.m_Y = m_Y / a;
		return result;
	}

	// 방향 바꾸기 단항 연산자
	const SVector2D operator -() {
		return SVector2D(-m_X, -m_Y);
	}

	// 복합대입연산자
	SVector2D& operator +=(const SVector2D& other) {
		return *this = *this + other;
	}

	SVector2D& operator -=(const SVector2D& other) {
		return *this = *this - other;
	}
	
	SVector2D& operator *=(const float scalar) {
		return *this = *this * scalar;
	}

	SVector2D& operator /= (const float scalar) {
		return *this = *this / scalar;
	}

	// 비교 연산자 (벡터에 비교라...)
	bool operator ==(const SVector2D& other) const {
		return (m_X == other.m_X) && (m_Y == other.m_Y);
	}

	bool operator !=(const SVector2D& other) const {
		return !(*this == other);
	}

	bool operator <(const SVector2D& other) const {
		if (m_X != other.m_X) {
			return m_X < other.m_X;
		}

		if (m_Y != other.m_Y) {
			return m_Y < other.m_Y;
		}

		return false;
	}

	// 내적
	float Dot(const SVector2D& other) const {
		return m_X * other.m_X + m_Y * other.m_Y;
	}

	// 유사 외적
	float Determinent(const SVector2D& other) const {
		return (m_X * other.m_Y) - (m_Y * other.m_X);
	}

	// 크기
	float size() const {
		/*float result = (sqrtf(m_X * m_X + m_Y * m_Y) */
		return sqrtf(Dot(*this));
	}

	float Distance(const SVector2D& other) const {
		return (*this - other).size();
	}

	// 정규화
	SVector2D Norm()const {
		const float length = size();
		// 한없이 0에 가까우면 그냥 0으로 치환
		if (length <= FLT_EPSILON) return SVector2D::ZERO;
		return *this / length;
	}

	SVector2D nomalization() {
		SVector2D result;
		result = *this / size();
		return result;
	}
	
	// 영벡터인지 확인
	bool IsZero() const {
		return *this == SVector2D::ZERO;
	}

};