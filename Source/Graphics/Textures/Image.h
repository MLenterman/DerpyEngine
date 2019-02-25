#pragma once

#include "../Colors/Color.h"
#include "../Colors/ColorUtils.h"
#include "../../Utils/MemoryUtils.h"

namespace Derpy { namespace Graphics {

	class Image{
	private:
		unsigned char* m_ImageData;
		unsigned int m_Width, m_Height;
		unsigned short m_BitsPerPixel;
		unsigned int m_Stride;
		EColorFormat m_Format;

	public:
		Image(EColorFormat format, const unsigned int& width, const unsigned int& height);
		Image(EColorFormat format, const unsigned int& width, const unsigned int& height, void* data);
		virtual ~Image();

		virtual void getDimensions(unsigned int& width, unsigned int& height) const;
		virtual unsigned int getStride() const;
		virtual unsigned int getBitsPerPixel() const;
		virtual unsigned int getBytesPerPixel() const;
		virtual unsigned int getImageDataSize() const;
		virtual unsigned int getPixelCount() const;
		virtual EColorFormat getColorFormat() const;

		virtual unsigned int getRedMask() const;
		virtual unsigned int getGreenMask() const;
		virtual unsigned int getBlueMask() const;
		virtual unsigned int getAlphaMask() const;

		virtual Color getPixel(unsigned int x, unsigned int y) const;
		virtual void setPixel(unsigned int x, unsigned int y, const Color &color, bool blend = false); // TODO: Blending

		// TODO <
		virtual void copyToScaling(void* target, unsigned int width, unsigned int height, EColorFormat format, unsigned int stride = 0);
		virtual void copyToScaling(Image* target);
		virtual void copyTo(Image* target, const int& width = 0, const int& height = 0);
		virtual void copyTo(Image* target, const int& posX, const int& posY, const int& sourceRectX, const int& sourceRectY, 
			const int* clipRectX = 0, const int* clipRectY = 0);
		virtual void copyToWithAlpha(Image* target, const int& posX, const int& posY, const int& sourceRectX, const int& sourceRectY, 
			const Color& color, const int* clipRectX = 0, const int* clipRectY = 0);
		virtual void copyToScalingBoxFilter(Image* target, unsigned int bias = 0, bool blend = false);
		// > TODO

		virtual void fill(const Color &color); // TODO: Color converts

	protected:
		void init();

		inline Color getPixelBox(int x, int y, int fx, int fy, int bias) const; // TODO
	};

} }