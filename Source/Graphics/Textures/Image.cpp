#include "Image.h"

namespace Derpy { namespace Graphics {

	Image::Image(EColorFormat format, const unsigned int& width, const unsigned int& height)
		: m_ImageData(NULL), m_Width(width), m_Height(height), m_Format(format){

		init();
	}

	Image::Image(EColorFormat format, const unsigned int& width, const unsigned int& height, void* data)
		: m_ImageData(NULL), m_Width(width), m_Height(height), m_Format(format){

		init();
		memcpy(m_ImageData, data, m_Height * m_Stride);
	}

	Image::~Image(){
		delete[] m_ImageData;
	}

	void Image::getDimensions(unsigned int& width, unsigned int& height) const{
		width = m_Width;
		height = m_Height;
	}

	unsigned int Image::getStride() const{
		return m_Stride;
	}
	
	unsigned int Image::getBitsPerPixel() const{
		return m_BitsPerPixel;
	}

	unsigned int Image::getBytesPerPixel() const{
		return m_BitsPerPixel / 8;
	}

	unsigned int Image::getImageDataSize() const{
		return m_Height * m_Stride;
	}

	unsigned int Image::getPixelCount() const{
		return m_Width * m_Height;
	}

	EColorFormat Image::getColorFormat() const{
		return m_Format;
	}

	unsigned int Image::getRedMask() const{
		switch (m_Format){
		case EColorFormat::A1R5G5B5:
			return 0x1F << 10;
		case EColorFormat::R5G6B5:
			return 0x1F << 11;
		case EColorFormat::R8G8B8:
			return 0x00FF0000;
		case EColorFormat::A8R8G8B8:
			return 0x00FF0000;
		default:
			return 0x0;
		}
	}

	unsigned int Image::getGreenMask() const{
		switch (m_Format){
		case EColorFormat::A1R5G5B5:
			return 0x1F << 5;
		case EColorFormat::R5G6B5:
			return 0x3F << 5;
		case EColorFormat::R8G8B8:
			return 0x0000FF00;
		case EColorFormat::A8R8G8B8:
			return 0x0000FF00;
		default:
			return 0x0;
		}
	}

	unsigned int Image::getBlueMask() const{
		switch (m_Format){
		case EColorFormat::A1R5G5B5:
			return 0x1F;
		case EColorFormat::R5G6B5:
			return 0x1F;
		case EColorFormat::R8G8B8:
			return 0x000000FF;
		case EColorFormat::A8R8G8B8:
			return 0x000000FF;
		default:
			return 0x0;
		}
	}

	unsigned int Image::getAlphaMask() const{
		switch (m_Format){
		case EColorFormat::A1R5G5B5:
			return 0x1 << 15;
		case EColorFormat::A8R8G8B8:
			return 0xFF000000;		
		default:
			return 0x0;
		}
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const{
		if (x >= m_Width || y >= m_Height)
			return Color(0);

		unsigned long index = y * m_Width + x;
		switch (m_Format){
		case EColorFormat::A1R5G5B5:
			return ColorUtils::fromA1R5G5B5toA8R8G8B8(((unsigned short*)m_ImageData)[index]);
		case EColorFormat::R5G6B5:
			return ColorUtils::fromR5G6B5toA8R8G8B8(((unsigned short*)m_ImageData)[index]);
		case EColorFormat::A8R8G8B8:
			return ((unsigned int*)m_ImageData)[index];
		case EColorFormat::R8G8B8:
			unsigned char* pixel = m_ImageData + (y * 3) * m_Width + (x * 3);
			return Color(255, *pixel, *++pixel, *++pixel);
		default:
			return Color(0);
		}
	}

	void Image::setPixel(unsigned int x, unsigned int y, const Color &color, bool blend = false){
		if (x >= m_Width || y >= m_Height)
			return;

		switch (m_Format){
		case EColorFormat::A1R5G5B5:
			unsigned short* destPixel = (unsigned short*)(m_ImageData + (y * m_Stride) + (x << 1));
			*destPixel = ColorUtils::fromA8R8G8B8toA1R5G5B5(color.color);
			break;

		case EColorFormat::R5G6B5:
			unsigned short* destPixel = (unsigned short*)(m_ImageData + (y * m_Stride) + (x << 1));
			*destPixel = ColorUtils::fromA8R8G8B8toR5G6B5(color.color);
			break;

		case EColorFormat::R8G8B8:
			unsigned char* destPixel = m_ImageData + (y * m_Stride) + (x * 3);
			*destPixel = (unsigned char)color.getRed();
			*++destPixel = (unsigned char)color.getGreen();
			*++destPixel = (unsigned char)color.getBlue();
			break;

		case EColorFormat::A8R8G8B8:
			*(unsigned int*)(m_ImageData + (y * m_Stride) + (x << 2)) = color.color;
			// TODO: Blending
			break;

		default:
			break;
		}
	}

	void Image::copyToScaling(void* target, unsigned int width, unsigned int height, EColorFormat format, unsigned int stride = 0){

	}

	void Image::copyToScaling(Image* target){

	}

	void Image::copyTo(Image* target, const int& width = 0, const int& height = 0){

	}

	void Image::copyTo(Image* target, const int& posX, const int& posY, const int& sourceRectX, const int& sourceRectY,
		const int* clipRectX = 0, const int* clipRectY = 0){

	}

	void Image::copyToWithAlpha(Image* target, const int& posX, const int& posY, const int& sourceRectX, const int& sourceRectY,
		const Color& color, const int* clipRectX = 0, const int* clipRectY = 0){

	}

	void Image::copyToScalingBoxFilter(Image* target, unsigned int bias = 0, bool blend = false){

	}

	void Image::fill(const Color &color){
		unsigned int col;

		switch (m_Format){
		case EColorFormat::A1R5G5B5:
			col = color.toA1R5G5B5();
			col |= col << 16;
			break;

		case EColorFormat::R5G6B5:
			col = ColorUtils::fromA8R8G8B8toR5G6B5(color.color);
			col |= col << 16;
			break;

		case EColorFormat::A8R8G8B8:
			col = color.color;
			break;

		case EColorFormat::R8G8B8:
			unsigned char rgb[3];
			//ColorUtils::fromA8R8G8B8toR8G8B8(&color, 1, rgb);
			const unsigned int size = getImageDataSize();
			for (unsigned int i = 0; i < size; i += 3)
				memcpy(m_ImageData + i, rgb, 3);
			return;

		default:
			col = 0xFFFFFFFF;
		}

		System::memset32(m_ImageData, col, getImageDataSize());
	}

	void Image::init(){
		m_BitsPerPixel = ColorUtils::getBitsPerPixel(m_Format);
		m_Stride = (m_BitsPerPixel / 8) * m_Width;

		if (!m_ImageData)
			m_ImageData = new unsigned char[m_Height * m_Stride];
	}

	inline Color Image::getPixelBox(int x, int y, int fx, int fy, int bias) const{
		return Color(0);
	}

} }