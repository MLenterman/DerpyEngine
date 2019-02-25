#include "Vec4f.h"

namespace Derpy { namespace Maths {

	Vec4f::Vec4f(const float& x, const float& y, const float& z, const float& w){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vec4f& Vec4f::add(const Vec4f& other){
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	Vec4f& Vec4f::subtract(const Vec4f& other){
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	Vec4f& Vec4f::multiply(const Vec4f& other){
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	Vec4f& Vec4f::divide(const Vec4f& other){
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	Vec4f operator+(Vec4f left, const Vec4f& right){
		return left.add(right);
	}

	Vec4f operator-(Vec4f left, const Vec4f& right){
		return left.subtract(right);
	}

	Vec4f operator*(Vec4f left, const Vec4f& right){
		return left.multiply(right);
	}

	Vec4f operator/(Vec4f left, const Vec4f& right){
		return left.divide(right);
	}

	Vec4f& Vec4f::operator+=(const Vec4f& other){
		return add(other);
	}

	Vec4f& Vec4f::operator-=(const Vec4f& other){
		return subtract(other);
	}

	Vec4f& Vec4f::operator*=(const Vec4f& other){
		return multiply(other);
	}

	Vec4f& Vec4f::operator/=(const Vec4f& other){
		return divide(other);
	}

	bool Vec4f::operator==(const Vec4f& other) const{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool Vec4f::operator!=(const Vec4f& other) const{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec4f& vector){
		stream << "Vec4f: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}

} }