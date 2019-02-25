#pragma once

#include <iostream>
#include "../../Maths/Maths.h"

namespace Derpy { namespace Graphics {

	enum class EColorFormat{
		UNKNOWN,
		A1R5G5B5,
		R5G6B5,
		R8G8B8,
		A8R8G8B8,
		R16F,
		G16R16F,
		A16B16G16R16F,
		R32F,
		G32R32F,
		A32B32G32R32F
	};


	class Color{
	public:
		unsigned int color;

	public:
		Color();
		Color(unsigned int alpha, unsigned int red, unsigned int green, unsigned int  blue);
		Color(unsigned int color);
		~Color();

		unsigned int getAlpha() const;
		unsigned int getRed() const;
		unsigned int getGreen() const;
		unsigned int getBlue() const;
		float getLightness() const;
		float getLuminance() const;
		unsigned int getAverage() const;

		void setAlpha(unsigned int alpha);
		void setRed(unsigned int red);
		void setGreen(unsigned int green);
		void setBlue(unsigned int blue);

		unsigned short toA1R5G5B5() const;
		void toOpenGLColor(unsigned char* dest) const;
		void set(unsigned int alpha, unsigned int red, unsigned int green, unsigned int blue);
		void set(unsigned int color);

		bool operator==(const Color& other) const;
		bool operator!=(const Color& other) const;
		bool operator<(const Color& other) const;

		Color operator+(const Color& other) const;

		Color getInterpolated(const Color &other, float d) const;
	};

} }