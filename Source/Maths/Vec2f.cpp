#include "Vec2f.h"

namespace Derpy { namespace Maths {

	Vec2f::Vec2f(){
		x = 0.0f;
		y = 0.0f;
	}

	Vec2f::Vec2f(const float& x, const float& y){
		this->x = x;
		this->y = y;
	}

	float Vec2f::getLength() const{
		return sqrt(x * x + y * y);
	}

	float Vec2f::getLengthSquared() const{
		return x * x + y * y;
	}

	float Vec2f::dotProduct(const Vec2f& other) const{
		return x * other.x + y * other.y;
	}

	float Vec2f::getDistanceFrom(const Vec2f& other) const{
		return Vec2f(
			x - other.x, 
			y - other.y).getLength();
	}

	float Vec2f::getDistanceFromSquared(const Vec2f& other) const{
		return Vec2f(
			x - other.x,
			y - other.y).getLengthSquared();
	}

	bool Vec2f::isBetweenPoints(const Vec2f& begin, const Vec2f& end) const{
		if (begin.x != end.x)
			return (begin.x <= x && x <= end.x) || (begin.x >= x && x >= end.x);
		else
			return (begin.y <= y && y <= end.y) || (begin.y >= y && y >= end.y);
	}

	Vec2f Vec2f::getInterpolated(const Vec2f& other, double d) const{
		double inv = 1.0f - d;

		return Vec2f(
			(float)(other.x * inv + x * d), 
			(float)(other.y * inv + y * d));
	}

	Vec2f& Vec2f::normalize(){
		float length = x * x + y * y;

		if (length == 0)
			return *this;

		length = invSqrt(length);
		x = x * length;
		y = y * length;
		return *this;
	}

	Vec2f& Vec2f::add(const Vec2f& other){
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2f& Vec2f::subtract(const Vec2f& other){
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vec2f& Vec2f::multiply(const Vec2f& other){
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vec2f& Vec2f::divide(const Vec2f& other){
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vec2f operator+(Vec2f left, const Vec2f& right){
		return left.add(right);
	}

	Vec2f operator-(Vec2f left, const Vec2f& right){
		return left.subtract(right);
	}

	Vec2f operator*(Vec2f left, const Vec2f& right){
		return left.multiply(right);
	}

	Vec2f operator/(Vec2f left, const Vec2f& right){
		return left.divide(right);
	}

	Vec2f& Vec2f::operator+=(const Vec2f& other){
		return add(other);
	}

	Vec2f& Vec2f::operator-=(const Vec2f& other){
		return subtract(other);
	}

	Vec2f& Vec2f::operator*=(const Vec2f& other){
		return multiply(other);
	}

	Vec2f& Vec2f::operator/=(const Vec2f& other){
		return divide(other);
	}

	bool Vec2f::operator==(const Vec2f& other) const{
		return x == other.x && y == other.y;
	}

	bool Vec2f::operator!=(const Vec2f& other) const{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec2f& vector){
		stream << "Vec2f: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

} }