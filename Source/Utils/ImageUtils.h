#pragma once

#include "../Graphics/Colors/Color.h"
#include "../Graphics/Colors/ColorUtils.h"
#include "../Utils/ByteUtils.h"

namespace Derpy { namespace Utils {

	class ImageUtils{
	public:
		static void convert1BitTo16Bit(const unsigned char* in, short* out, int width, int height, int linepad = 0, bool flip = false);
		static void convert4BitTo16Bit(const unsigned char* in, short* out, int width, int height, const int* palette, int linepad = 0, bool flip = false);
		static void convert8BitTo16Bit(const unsigned char* in, short* out, int width, int height, const int* palette, int linepad = 0, bool flip = false);
		static void convert8BitTo24Bit(const unsigned char* in, unsigned char* out, int width, int height, const unsigned char* palette, int linepad = 0, bool flip = false);
		static void convert8BitTo32Bit(const unsigned char* in, unsigned char* out, int width, int height, const unsigned char* palette, int linepad = 0, bool flip = false);
		static void convert16BitTo16Bit(const short* in, short* out, int width, int height, int linepad = 0, bool flip = false);
		static void convert24BitTo24Bit(const unsigned char* in, unsigned char* out, int width, int height, int linepad = 0, bool flip = false, bool bgr = false);
		// SLOW !!!
		static void convert16bitToA8R8G8B8andResize(const short* in, int* out, int newWidth, int newHeight, int currentWidth, int currentHeight);
		static void convert32BitTo32Bit(const int* in, int* out, int width, int height, int linepad, bool flip = false);

		static void convertA1R5G5B5toR8G8B8(const void* source, int pixelCount, void* dest);
		static void convertA1R5G5B5toB8G8R8(const void* source, int pixelCount, void* dest);
		static void convertA1R5G5B5toA8R8G8B8(const void* source, int pixelCount, void* dest);
		static void convertA1R5G5B5toA1R5G5B5(const void* source, int pixelCount, void* dest);
		static void convertA1R5G5B5toR5G6B5(const void* source, int pixelCount, void* dest);

		static void convertA8R8G8B8toR8G8B8(const void* source, int pixelCount, void* dest);
		static void convertA8R8G8B8toB8G8R8(const void* source, int pixelCount, void* dest);
		static void convertA8R8G8B8toA8R8G8B8(const void* source, int pixelCount, void* dest);
		static void convertA8R8G8B8toA1R5G5B5(const void* source, int pixelCount, void* dest);
		static void convertA8R8G8B8toR5G6B5(const void* source, int pixelCount, void* dest);

		static void convertA8R8G8B8toR3G3B2(const void* source, int pixelCount, void* dest);
		static void convertR8G8B8toR8G8B8(const void* source, int pixelCount, void* dest);
		static void convertR8G8B8toA8R8G8B8(const void* source, int pixelCount, void* dest);
		static void convertR8G8B8toA1R5G5B5(const void* source, int pixelCount, void* dest);
		static void convertR8G8B8toR5G6B5(const void* source, int pixelCount, void* dest);
		static void convertB8G8R8toA8R8G8B8(const void* source, int pixelCount, void* dest);
		static void convertB8G8R8A8toA8R8G8B8(const void* source, int pixelCount, void* dest);

		static void convertR5G6B5toR5G6B5(const void* source, int pixelCount, void* dest);
		static void convertR5G6B5toR8G8B8(const void* source, int pixelCount, void* dest);
		static void convertR5G6B5toB8G8R8(const void* source, int pixelCount, void* dest);
		static void convertR5G6B5toA8R8G8B8(const void* source, int pixelCount, void* dest);
		static void convertR5G6B5toA1R5G5B5(const void* source, int pixelCount, void* dest);
		static void convert(const void* source, Graphics::EColorFormat sourceFormat, int pixelCount,
			void* dest, Graphics::EColorFormat destFormat);
	};

} }