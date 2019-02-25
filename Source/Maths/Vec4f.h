#pragma once

#include <iostream>

namespace Derpy { namespace Maths {

	struct Vec4f{
		float x, y, z, w;

		Vec4f() = default;
		Vec4f(const float& x, const float& y, const float& z, const float& w);

		Vec4f& add(const Vec4f& other);
		Vec4f& subtract(const Vec4f& other);
		Vec4f& multiply(const Vec4f& other);
		Vec4f& divide(const Vec4f& other);

		friend Vec4f operator+(Vec4f left, const Vec4f& right);
		friend Vec4f operator-(Vec4f left, const Vec4f& right);
		friend Vec4f operator*(Vec4f left, const Vec4f& right);
		friend Vec4f operator/(Vec4f left, const Vec4f& right);

		bool operator==(const Vec4f& other) const;
		bool operator!=(const Vec4f& other) const;

		Vec4f& operator+=(const Vec4f& other);
		Vec4f& operator-=(const Vec4f& other);
		Vec4f& operator*=(const Vec4f& other);
		Vec4f& operator/=(const Vec4f& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vec4f& vector);
	};

} }