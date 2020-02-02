#include "Mat4f.h"

namespace Derpy { namespace Maths {

	Mat4f::Mat4f() 
			: elements{} // Empty braced-list equals initialize to 0
	{
		
	}

	Mat4f::Mat4f(
		float diagonal)
			: elements{} // Empty braced-list equals initialize to 0
	{
		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	Mat4f 
		Mat4f::identity()
	{
		return Mat4f(1.0f);
	}

	Mat4f& 
		Mat4f::multiply(
			const Mat4f& right)
	{
		std::array<float, 16> data;

		for (int y = 0; y < 4; y++){
			for (int x = 0; x < 4; x++){
				float sum = 0.0f;

				for (int e = 0; e < 4; e++){
					sum += elements[x + e * 4] * right.elements[e + y * 4];
				}

				data[x + y * 4] = sum;
			}
		}

		std::copy(data.begin(), data.end(), elements);

		return *this;
	}

	Vec3f 
		Mat4f::multiply(
			const Vec3f& right) const
	{
		return Vec3f(
			elements[0 + 0 * SIZE] * right.x + elements[1 + 0 * SIZE] * right.y + elements[2 + 0 * SIZE] * right.z + elements[3 + 0 * SIZE],
			elements[0 + 1 * SIZE] * right.x + elements[1 + 1 * SIZE] * right.y + elements[2 + 1 * SIZE] * right.z + elements[3 + 1 * SIZE],
			elements[0 + 2 * SIZE] * right.x + elements[1 + 2 * SIZE] * right.y + elements[2 + 2 * SIZE] * right.z + elements[3 + 2 * SIZE]
			);
	}

	Vec4f 
		Mat4f::multiply(
			const Vec4f& right) const
	{
		return Vec4f(
			elements[0 + 0 * SIZE] * right.x + elements[1 + 0 * SIZE] * right.y + elements[2 + 0 * SIZE] * right.z + elements[3 + 0 * SIZE] * right.w,
			elements[0 + 1 * SIZE] * right.x + elements[1 + 1 * SIZE] * right.y + elements[2 + 1 * SIZE] * right.z + elements[3 + 1 * SIZE] * right.w,
			elements[0 + 2 * SIZE] * right.x + elements[1 + 2 * SIZE] * right.y + elements[2 + 2 * SIZE] * right.z + elements[3 + 2 * SIZE] * right.w,
			elements[0 + 3 * SIZE] * right.x + elements[1 + 3 * SIZE] * right.y + elements[2 + 3 * SIZE] * right.z + elements[3 + 3 * SIZE] * right.w
			);
	}

	Mat4f 
		operator*(
			Mat4f left, 
			const Mat4f& right)
	{
		return left.multiply(right);
	}

	Mat4f& 
		Mat4f::operator*=(
			const Mat4f& right)
	{
		return multiply(right);
	}

	Vec3f 
		operator*(
			const Mat4f& left, 
			const Vec3f& right)
	{
		return left.multiply(right);
	}
	
	Vec4f 
		operator*(
			const Mat4f& left, 
			const Vec4f& right)
	{
		return left.multiply(right);
	}
	
	Mat4f& 
		Mat4f::invert()
	{
		double temp[16];

		temp[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];

		temp[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];

		temp[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];

		temp[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];

		temp[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];

		temp[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];

		temp[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];

		temp[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];

		temp[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];

		temp[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];

		temp[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];

		temp[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];

		temp[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];

		temp[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];

		temp[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];

		temp[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];

		double determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
		determinant = 1.0 / determinant;

		for(int i = 0; i < 4 * 4; i++)
			elements[i] = temp[i] * determinant;

		return *this;
	}

	Mat4f 
		Mat4f::orthographic(
			float left, 
			float right, 
			float bottom, 
			float top, 
			float near, 
			float far)
	{
		Mat4f result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	Mat4f 
		Mat4f::perspective(
			float fov, 
			float aspectRatio, 
			float near, 
			float far)
	{
		Mat4f result(1.0f);

		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}

	Mat4f 
		Mat4f::translation(
			const Vec3f& translation)
	{
		Mat4f result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}

	Mat4f 
		Mat4f::rotation(
			float angle, 
			const Vec3f& axis)
	{
		Mat4f result(1.0f);

		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[1 + 0 * 4] = y * x * omc + z * s;
		result.elements[2 + 0 * 4] = x * z * omc - y * s;

		result.elements[0 + 1 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[2 + 1 * 4] = y * z * omc + x * s;

		result.elements[0 + 2 * 4] = x * z * omc + y * s;
		result.elements[1 + 2 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;

		return result;
	}

	Mat4f 
		Mat4f::scale(
			const Vec3f& scale)
	{
		Mat4f result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

} }