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

	// �⺻ ������ �����ε�
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

	// ��Į�� ���ε� ���ϰ� �Ϸ��� ���� ���� ���ϰ� �ϱ� ���ؼ�
	const SVector2D operator /(const float& a) const {
		SVector2D result;
		result.m_X = m_X / a;
		result.m_Y = m_Y / a;
		return result;
	}

	// ���� �ٲٱ� ���� ������
	const SVector2D operator -() {
		return SVector2D(-m_X, -m_Y);
	}

	// ���մ��Կ�����
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

	// �� ������ (���Ϳ� �񱳶�...)
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

	// ����
	float Dot(const SVector2D& other) const {
		return m_X * other.m_X + m_Y * other.m_Y;
	}

	// ���� ����
	float Determinent(const SVector2D& other) const {
		return (m_X * other.m_Y) - (m_Y * other.m_X);
	}

	// ũ��
	float size() const {
		/*float result = (sqrtf(m_X * m_X + m_Y * m_Y) */
		return sqrtf(Dot(*this));
	}

	float Distance(const SVector2D& other) const {
		return (*this - other).size();
	}

	// ����ȭ
	SVector2D Norm()const {
		const float length = size();
		// �Ѿ��� 0�� ������ �׳� 0���� ġȯ
		if (length <= FLT_EPSILON) return SVector2D::ZERO;
		return *this / length;
	}

	SVector2D nomalization() {
		SVector2D result;
		result = *this / size();
		return result;
	}
	
	// ���������� Ȯ��
	bool IsZero() const {
		return *this == SVector2D::ZERO;
	}

};