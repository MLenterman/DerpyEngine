#pragma once

#include <array>

#include "Vec3f.h"
#include "Vec4f.h"
#include "Math_Funcs.h"

/* TODO
	- Use std::array? replace memcpy with std::copy, possible performance increase?
	- invert() : Fix float to double coversion
	- Research if its worth the overhead of allocation on the heap, to support move semantics?
*/

namespace Derpy { namespace Maths {

	struct Mat4f{
		const static int SIZE = 4;
		float elements[16];

		Mat4f();

		Mat4f(
			float diagonal);

		static Mat4f 
			identity();

		Mat4f& 
			multiply(
				const Mat4f& right);

		friend Mat4f 
			operator*(
				Mat4f left, 
				const Mat4f& right);

		Mat4f& 
			operator*=(
				const Mat4f& right);

		Vec3f 
			multiply(
				const Vec3f& right) const;

		friend Vec3f 
			operator*(
				const Mat4f& left, 
				const Vec3f& right);

		Vec4f 
			multiply(
				const Vec4f& right) const;

		friend Vec4f 
			operator*(
				const Mat4f& left, 
				const Vec4f& right);

		Mat4f& 
			invert();

		static Mat4f 
			orthographic(
				float left, 
				float right, 
				float bottom, 
				float top, 
				float near, 
				float far);

		static Mat4f 
			perspective(
				float fov, 
				float aspectRatio, 
				float near, 
				float far);

		static Mat4f 
			translation(
				const Vec3f& translation);

		static Mat4f 
			rotation(
				float angle, 
				const Vec3f& axis);

		static Mat4f 
			scale(
				const Vec3f& scale);
	};

} }