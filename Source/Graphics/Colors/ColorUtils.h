#pragma once

#include "Color.h"

namespace Derpy { namespace Graphics {

	class ColorUtils{
	public:
		static inline unsigned short toRGBA16(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 0xFF){
			return (unsigned short)((alpha & 0x80) << 8 |
				(red & 0xF8) << 7 |
				(green & 0xF8) << 2 |
				(blue & 0xF8) >> 3);
		}
		
		static inline unsigned short toRGB16(unsigned int red, unsigned int green, unsigned int blue){
			return toRGBA16(red, green, blue);
		}
		
		static inline unsigned short from16toRGB16(unsigned short red, unsigned short green, unsigned short blue){
			return (0x8000 |
				(red & 0x1F) << 10 |
				(green & 0x1F) << 5 |
				(blue & 0x1F));
		}
		
		static inline unsigned short fromX8R8G8B8toA1R5G5B5(unsigned int color){
			return (unsigned short)(0x8000 |
				(color & 0x00F80000) >> 9 |
				(color & 0x0000F800) >> 6 |
				(color & 0x000000F8) >> 3);
		}
		
		static inline unsigned short fromA8R8G8B8toA1R5G5B5(unsigned int color){
			return (unsigned short)((color & 0x80000000) >> 16 |
				(color & 0x00F80000) >> 9 |
				(color & 0x0000F800) >> 6 |
				(color & 0x000000F8) >> 3);
	    }
		
		static inline unsigned short fromA8R8G8B8toR5G6B5(unsigned int color){
			return (unsigned short)((color & 0x00F80000) >> 8 |
				(color & 0x0000FC00) >> 5 |
				(color & 0x000000F8) >> 3);
		}
		
		static inline unsigned int fromA1R5G5B5toA8R8G8B8(unsigned short color){ /// minus
			return (((((unsigned int)color & 0x00008000) >> (unsigned int)31) & 0xFF000000) |
				((color & 0x00007C00) << 9) | ((color & 0x00007000) << 4) |
				((color & 0x000003E0) << 6) | ((color & 0x00000380) << 1) |
				((color & 0x0000001F) << 3) | ((color & 0x0000001C) >> 2));
		}
		
		static inline unsigned int fromR5G6B5toA8R8G8B8(unsigned short color){
			return 0xFF000000 |
				((color & 0xF800) << 8) |
				((color & 0x07E0) << 5) |
				((color & 0x001F) << 3);
		}
		
		static inline unsigned short fromR5G6B5toA1R5G5B5(unsigned short color){
			return 0x8000 | (((color & 0xFFC0) >> 1) | (color & 0x1F));
		}
		
		static inline unsigned short fromA1R5G5B5toR5G6B5(unsigned short color){
			return (((color & 0x7FE0) << 1) | (color & 0x1F));
		}
		
		static inline unsigned int getAlpha(unsigned short color){
			return ((color >> 15) & 0x1);
		}
		
		static inline unsigned int getRed(unsigned short color){
			return ((color >> 10) & 0x1F);
		}
		
		static inline unsigned int getGreen(unsigned short color){
			return ((color >> 5) & 0x1F);
		}
		
		static inline unsigned int getBlue(unsigned short color){
			return (color & 0x1F);
		}
		
		static inline unsigned int getAverage(unsigned short color){
			return ((getRed(color) << 3) + (getGreen(color) << 3) + (getBlue(color) << 3)) / 3;
		}

		static inline unsigned short getBitsPerPixel(EColorFormat format){
			switch (format){
			case EColorFormat::A1R5G5B5:
				return 16;
			case EColorFormat::R5G6B5:
				return 16;
			case EColorFormat::R8G8B8:
				return 24;
			case EColorFormat::A8R8G8B8:
				return 32;
			case EColorFormat::R16F:
				return 16;
			case EColorFormat::G16R16F:
				return 32;
			case EColorFormat::A16B16G16R16F:
				return 64;
			case EColorFormat::R32F:
				return 32;
			case EColorFormat::G32R32F:
				return 64;
			case EColorFormat::A32B32G32R32F:
				return 128;
			default:
				return 0;
			}
		}

	protected:
		ColorUtils() { }
		~ColorUtils() { }
	};




} }