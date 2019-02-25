#pragma once

#include <iostream>

#include "Math_Funcs.h"

namespace Derpy { namespace Maths {

	struct Vec3f{
		float x, y, z;

		Vec3f();
		Vec3f(const float& x, const float& y, const float& z);

		Maths::Vec3f& invert();
		float getLength() const;
		float getLengthSquared() const;
		float dotProduct(const Maths::Vec3f& other) const;
		float getDistanceFrom(const Maths::Vec3f& other) const;
		float getDistanceFromSquared(const Maths::Vec3f& other) const;
		Maths::Vec3f crossProduct(const Maths::Vec3f& p) const;
		bool isBetweenPoints(const Maths::Vec3f& begin, const Maths::Vec3f& end) const;
		Vec3f getInterpolated(const Vec3f& other, double d) const;
		Maths::Vec3f& normalize();

		Vec3f& add(const Vec3f& other);
		Vec3f& subtract(const Vec3f& other);
		Vec3f& multiply(const Vec3f& other);
		Vec3f& divide(const Vec3f& other);

		friend Vec3f operator+(Vec3f left, const Vec3f& right);
		friend Vec3f operator-(Vec3f left, const Vec3f& right);
		friend Vec3f operator*(Vec3f left, const Vec3f& right);
		friend Vec3f operator/(Vec3f left, const Vec3f& right);

		bool operator==(const Vec3f& other) const;
		bool operator!=(const Vec3f& other) const;

		Vec3f& operator+=(const Vec3f& other);
		Vec3f& operator-=(const Vec3f& other);
		Vec3f& operator*=(const Vec3f& other);
		Vec3f& operator/=(const Vec3f& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vec3f& vector);
	};

} }