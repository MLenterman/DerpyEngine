#pragma once

#include <iostream>

#include "Math_Funcs.h"

namespace Derpy { namespace Maths {

	struct Vec2f{
		float x, y;

		Vec2f();
		Vec2f(const float& x, const float& y);

		float getLength() const;
		float getLengthSquared() const;
		float dotProduct(const Vec2f& other) const;
		float getDistanceFrom(const Vec2f& other) const;
		float getDistanceFromSquared(const Vec2f& other) const;
		bool isBetweenPoints(const Vec2f& begin, const Vec2f& end) const;
		Vec2f getInterpolated(const Vec2f& other, double d) const;
		Vec2f& normalize();


		Vec2f& add(const Vec2f& other);
		Vec2f& subtract(const Vec2f& other);
		Vec2f& multiply(const Vec2f& other);
		Vec2f& divide(const Vec2f& other);

		friend Vec2f operator+(Vec2f left, const Vec2f& right);
		friend Vec2f operator-(Vec2f left, const Vec2f& right);
		friend Vec2f operator*(Vec2f left, const Vec2f& right);
		friend Vec2f operator/(Vec2f left, const Vec2f& right);

		bool operator==(const Vec2f& other) const;
		bool operator!=(const Vec2f& other) const;

		Vec2f& operator+=(const Vec2f& other);
		Vec2f& operator-=(const Vec2f& other);
		Vec2f& operator*=(const Vec2f& other);
		Vec2f& operator/=(const Vec2f& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vec2f& vector);
	};

} }