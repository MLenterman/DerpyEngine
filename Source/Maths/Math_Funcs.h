#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace Derpy { namespace Maths {

	inline float toRadians(float degrees){
		return degrees * (M_PI / 180.0f);
	}

	/*
	Credits to Gary Tarolli for this awsomely fast function.
	Code from Quake3 engine.
	*/
	inline float invSqrt(float x){
		float xhalf = 0.5f * x;
		int i = *(int*)&x;
		i = 0x5f3759df - (i >> 1);
		x = *(float*)&i;
		x = x*(1.5f - xhalf * x * x);
		return x;
	}

	template<class T>
	inline const T& min(const T& a, const T& b){
		return a < b ? a : b;
	}
	
	template<class T>
	inline const T& min(const T& a, const T& b, const T& c){
		return a < b ? min(a, c) : min(b, c);
	}
	
	template<class T>
	inline const T& max(const T& a, const T& b){
		return a < b ? b : a;
	}
	
	template<class T>
	inline const T& max(const T& a, const T& b, const T& c){
		return a < b ? max(b, c) : max(a, c);
	}

	template <class T>
	inline const T clamp(const T& value, const T& low, const T& high){
		return min(max(value, low), high);
	}

	inline int round32(float x){
		int i;

		// Assembly SSE CPU instruction(SIMD) for rounding
		__asm{
			fld   x
			fistp i
		}

		return i;
	}

} }