#include "Vec3f.h"

namespace Derpy { namespace Maths {

	Vec3f::Vec3f(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vec3f::Vec3f(const float& x, const float& y, const float& z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Maths::Vec3f& Vec3f::invert(){
		x *= -1;
		y *= -1;
		z *= -1;
		return *this;
	}

	float Vec3f::getLength() const{
		return sqrt(x * x + y * y + z * z);
	}

	float Vec3f::getLengthSquared() const{
		return x * x + y * y + z * z;
	}

	float Vec3f::dotProduct(const Maths::Vec3f& other) const{
		return x * other.x + y * other.y + z * other.z;
	}

	float Vec3f::getDistanceFrom(const Maths::Vec3f& other) const{
		return Maths::Vec3f(
			x - other.x, 
			y - other.y, 
			z - other.z).getLength();
	}

	float Vec3f::getDistanceFromSquared(const Maths::Vec3f& other) const{
		return Maths::Vec3f(
			x - other.x, 
			y - other.y, 
			z - other.z).getLengthSquared();
	}

	Maths::Vec3f Vec3f::crossProduct(const Maths::Vec3f& p) const{
		return Maths::Vec3f(
			y * p.z - z * p.y,
			z * p.x - x * p.z, 
			x * p.y - y * p.x);
	}

	bool Vec3f::isBetweenPoints(const Maths::Vec3f& begin, const Maths::Vec3f& end) const{
		const float dist = (end - begin).getLengthSquared();
		return getDistanceFromSquared(begin) <= dist && getDistanceFromSquared(end) <= dist;
	}

	Vec3f Vec3f::getInterpolated(const Vec3f& other, double d) const{
		const double inv = 1.0 - d;

		return Vec3f(
			(float)(other.x * inv + x * d), 
			(float)(other.y * inv + y * d), 
			(float)(other.z * inv + z * d));
	}

	Maths::Vec3f& Vec3f::normalize(){
		double length = x * x + y * y + z * z;

		if (length == 0)
			return *this;
		
		length = invSqrt(length);
		x = (float)(x * length);
		y = (float)(y * length);
		z = (float)(z * length);
		return *this;
	}

	Vec3f& Vec3f::add(const Vec3f& other){
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vec3f& Vec3f::subtract(const Vec3f& other){
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vec3f& Vec3f::multiply(const Vec3f& other){
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Vec3f& Vec3f::divide(const Vec3f& other){
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	Vec3f operator+(Vec3f left, const Vec3f& right){
		return left.add(right);
	}

	Vec3f operator-(Vec3f left, const Vec3f& right){
		return left.subtract(right);
	}

	Vec3f operator*(Vec3f left, const Vec3f& right){
		return left.multiply(right);
	}

	Vec3f operator/(Vec3f left, const Vec3f& right){
		return left.divide(right);
	}

	Vec3f& Vec3f::operator+=(const Vec3f& other){
		return add(other);
	}

	Vec3f& Vec3f::operator-=(const Vec3f& other){
		return subtract(other);
	}

	Vec3f& Vec3f::operator*=(const Vec3f& other){
		return multiply(other);
	}

	Vec3f& Vec3f::operator/=(const Vec3f& other){
		return divide(other);
	}

	bool Vec3f::operator==(const Vec3f& other) const{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vec3f::operator!=(const Vec3f& other) const{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3f& vector){
		stream << "Vec3f: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

} }