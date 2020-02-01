#include "ImageUtils.h"

namespace Derpy { namespace Utils {

	void ImageUtils::convert1BitTo16Bit(const unsigned char* in, short* out, int width, int height, int linepad, bool flip){
		if (!in || !out)
			return;

		if (flip)
			out += width * height;

		for (int y = 0; y < height; y++){
			int shift = 7;

			if (flip)
				out -= width;

			for (int x = 0; x < width; x++){
				out[x] = *in >> shift & 0x01 ? (short)0xffff : (short)0x8000;

				if (--shift < 0){
					shift = 7;
					++in;
				}
			}

			if (shift != 7)
				in++;

			if (!flip)
				out += width;

			in += linepad;
		}
	}

	void ImageUtils::convert4BitTo16Bit(const unsigned char* in, short* out, int width, int height, const int* palette, int linepad, bool flip){
		if (!in || !out || !palette)
			return;

		if (flip)
			out += width*height;

		for (int y = 0; y < height; y++){
			int shift = 4;

			if (flip)
				out -= width;

			for (int x = 0; x < width; x++){
				out[x] = Graphics::ColorUtils::fromX8R8G8B8toA1R5G5B5(palette[(unsigned char)((*in >> shift) & 0xf)]);

				if (shift == 0){
					shift = 4;
					in++;
				}
				else
					shift = 0;
			}

			if (shift == 0)
				++in;

			if (!flip)
				out += width;

			in += linepad;
		}
	}

	void ImageUtils::convert8BitTo16Bit(const unsigned char* in, short* out, int width, int height, const int* palette, int linepad, bool flip){
		if (!in || !out || !palette)
			return;

		if (flip)
			out += width * height;

		for (int y = 0; y < height; y++){
			if (flip)
				out -= width;

			for (int x = 0; x < width; x++){
				out[x] = Graphics::ColorUtils::fromX8R8G8B8toA1R5G5B5(palette[(unsigned char)(*in)]);
				++in;
			}

			if (!flip)
				out += width;
			
			in += linepad;
		}
	}

	void ImageUtils::convert8BitTo24Bit(const unsigned char* in, unsigned char* out, int width, int height, const unsigned char* palette, int linepad, bool flip){
		if (!in || !out)
			return;

		const int lineWidth = 3 * width;

		if (flip)
			out += lineWidth * height;

		for (int y = 0; y < height; y++){
			if (flip)
				out -= lineWidth;

			for (int x = 0; x < lineWidth; x += 3){
				if (palette){
#ifdef __BIG_ENDIAN__
					out[x + 0] = palette[(in[0] << 2) + 0];
					out[x + 1] = palette[(in[0] << 2) + 1];
					out[x + 2] = palette[(in[0] << 2) + 2];
#else
					out[x + 0] = palette[(in[0] << 2) + 2];
					out[x + 1] = palette[(in[0] << 2) + 1];
					out[x + 2] = palette[(in[0] << 2) + 0];
#endif
				}
				else{
					out[x + 0] = in[0];
					out[x + 1] = in[0];
					out[x + 2] = in[0];
				}

				++in;
			}

			if (!flip)
				out += lineWidth;

			in += linepad;
		}
	}

	void ImageUtils::convert8BitTo32Bit(const unsigned char* in, unsigned char* out, int width, int height, const unsigned char* palette, int linepad, bool flip){
		if (!in || !out)
			return;

		const unsigned int lineWidth = 4 * width;

		if (flip)
			out += lineWidth * height;

		unsigned int x;
		register unsigned int c;
		for (unsigned int y = 0; y < (unsigned int)height; y++){
			if (flip)
				out -= lineWidth;

			if (palette){
				for (x = 0; x < (unsigned int)width; x += 1){
					c = in[x];
					((unsigned int*)out)[x] = ((unsigned int*)palette)[c];
				}
			}
			else{
				for (x = 0; x < (unsigned int)width; x += 1){
					c = in[x];
#ifdef __BIG_ENDIAN__
					((unsigned int*)out)[x] = c << 24 | c << 16 | c << 8 | 0x000000FF;
#else
					((unsigned int*)out)[x] = 0xFF000000 | c << 16 | c << 8 | c;
#endif
				}

			}

			if (!flip)
				out += lineWidth;

			in += width + linepad;
		}
	}

	void ImageUtils::convert16BitTo16Bit(const short* in, short* out, int width, int height, int linepad, bool flip){
		if (!in || !out)
			return;

		if (flip)
			out += width * height;

		for (int y = 0; y < height; y++){
			if (flip)
				out -= width;

#ifdef __BIG_ENDIAN__
			for (int x = 0; x < width; x++)
				out[x] = Utils::Byteswap::byteswap(in[x]);
#else
			memcpy(out, in, width * sizeof(short));
#endif
			if (!flip)
				out += width;

			in += width;
			in += linepad;
		}
	}

	void ImageUtils::convert24BitTo24Bit(const unsigned char* in, unsigned char* out, int width, int height, int linepad, bool flip, bool bgr){
		if (!in || !out)
			return;

		const int lineWidth = 3 * width;

		if (flip)
			out += lineWidth * height;

		for (int y = 0; y < height; y++){
			if (flip)
				out -= lineWidth;

			if (bgr){
				for (int x = 0; x < lineWidth; x += 3){
					out[x + 0] = in[x + 2];
					out[x + 1] = in[x + 1];
					out[x + 2] = in[x + 0];
				}
			}
			else{
				memcpy(out, in, lineWidth);
			}

			if (!flip)
				out += lineWidth;

			in += lineWidth;
			in += linepad;
		}
	}

	void ImageUtils::convert16bitToA8R8G8B8andResize(const short* in, int* out, int newWidth, int newHeight, int currentWidth, int currentHeight){
		if (!newWidth || !newHeight)
			return;	

		float sourceXStep = (float)currentWidth / (float)newWidth;
		float sourceYStep = (float)currentHeight / (float)newHeight;
		float sy;
		int t;

		for (int x = 0; x < newWidth; x++){
			sy = 0.0f;

			for (int y = 0; y < newHeight; y++){
				t = in[(int)(((int)sy) * currentWidth + x * sourceXStep)];
				t = (((t >> 15) & 0x1) << 31) | (((t >> 10) & 0x1F) << 19) |
					(((t >> 5) & 0x1F) << 11) | (t & 0x1F) << 3;
				out[(int)(y * newWidth + x)] = t;

				sy += sourceYStep;
			}
		}
	}

	void ImageUtils::convert32BitTo32Bit(const int* in, int* out, int width, int height, int linepad, bool flip){
		if (!in || !out)
			return;

		if (flip)
			out += width * height;

		for (int y = 0; y < height; y++){
			if (flip)
				out -= width;

#ifdef __BIG_ENDIAN__
			for (int x = 0; x < width; x++)
				out[x] = Utils::Byteswap::byteswap(in[x]);
#else
			memcpy(out, in, width*sizeof(int));
#endif
			if (!flip)
				out += width;

			in += width;
			in += linepad;
		}
	}

	void ImageUtils::convertA1R5G5B5toR8G8B8(const void* source, int pixelCount, void* dest){
		unsigned short* sourceBuff = (unsigned short*)source;
		unsigned char * destBuff = (unsigned char *)dest;

		for (int x = 0; x < pixelCount; x++){
			destBuff[2] = (*sourceBuff & 0x7c00) >> 7;
			destBuff[1] = (*sourceBuff & 0x03e0) >> 2;
			destBuff[0] = (*sourceBuff & 0x1f) << 3;

			sourceBuff += 1;
			destBuff += 3;
		}
	}

	void ImageUtils::convertA1R5G5B5toB8G8R8(const void* source, int pixelCount, void* dest){
		unsigned short* sourceBuff = (unsigned short*)source;
		unsigned char * destBuff = (unsigned char *)dest;

		for (int x = 0; x < pixelCount; x++){
			destBuff[0] = (*sourceBuff & 0x7c00) >> 7;
			destBuff[1] = (*sourceBuff & 0x03e0) >> 2;
			destBuff[2] = (*sourceBuff & 0x1f) << 3;

			sourceBuff += 1;
			destBuff += 3;
		}
	}

	void ImageUtils::convertA1R5G5B5toA8R8G8B8(const void* source, int pixelCount, void* dest){
		unsigned short* sourceBuff = (unsigned short*)source;
		unsigned int* destBuff = (unsigned int*)dest;

		for (int x = 0; x < pixelCount; x++)
			*destBuff++ = Graphics::ColorUtils::fromA1R5G5B5toA8R8G8B8(*sourceBuff++);
	}

	void ImageUtils::convertA1R5G5B5toA1R5G5B5(const void* source, int pixelCount, void* dest){
		memcpy(dest, source, pixelCount * 2);
	}

	void ImageUtils::convertA1R5G5B5toR5G6B5(const void* source, int pixelCount, void* dest){
		unsigned short* sourceBuff = (unsigned short*)source;
		unsigned short* destBuff = (unsigned short*)dest;

		for (int x = 0; x < pixelCount; x++)
			*destBuff++ = Graphics::ColorUtils::fromA1R5G5B5toR5G6B5(*sourceBuff++);
	}

	void ImageUtils::convertA8R8G8B8toR8G8B8(const void* source, int pixelCount, void* dest){
		unsigned char* sourceBuff = (unsigned char*)source;
		unsigned char* destBuff = (unsigned char*)dest;

		for (int x = 0; x < pixelCount; x++){
			destBuff[0] = sourceBuff[2];
			destBuff[1] = sourceBuff[1];
			destBuff[2] = sourceBuff[0];

			sourceBuff += 4;
			destBuff += 3;
		}
	}

	void ImageUtils::convertA8R8G8B8toB8G8R8(const void* source, int pixelCount, void* dest){
		unsigned char* sourceBuff = (unsigned char*)source;
		unsigned char* destBuff = (unsigned char*)dest;

		for (int x = 0; x < pixelCount; x++){
			destBuff[0] = sourceBuff[0];
			destBuff[1] = sourceBuff[1];
			destBuff[2] = sourceBuff[2];

			sourceBuff += 4;
			destBuff += 3;
		}
	}

	void ImageUtils::convertA8R8G8B8toA8R8G8B8(const void* source, int pixelCount, void* dest){
		memcpy(dest, source, pixelCount * 4);
	}

	void ImageUtils::convertA8R8G8B8toA1R5G5B5(const void* source, int pixelCount, void* dest){
		unsigned int* sourceBuff = (unsigned int*)source;
		unsigned short* destBuff = (unsigned short*)dest;

		for (int x = 0; x < pixelCount; x++)
			*destBuff++ = Graphics::ColorUtils::fromA8R8G8B8toA1R5G5B5(*sourceBuff++);
	}

	void ImageUtils::convertA8R8G8B8toR5G6B5(const void* source, int pixelCount, void* dest){
		unsigned char * sourceBuff = (unsigned char *)source;
		unsigned short* destBuff = (unsigned short*)dest;

		for (int x = 0; x < pixelCount; x++){
			int r = sourceBuff[2] >> 3;
			int g = sourceBuff[1] >> 2;
			int b = sourceBuff[0] >> 3;

			destBuff[0] = (r << 11) | (g << 5) | (b);

			sourceBuff += 4;
			destBuff += 1;
		}
	}

	void ImageUtils::convertA8R8G8B8toR3G3B2(const void* source, int pixelCount, void* dest){
		unsigned char* sourceBuff = (unsigned char*)source;
		unsigned char* destBuff = (unsigned char*)dest;

		for (int x = 0; x < pixelCount; x++){
			unsigned char r = sourceBuff[2] & 0xe0;
			unsigned char g = (sourceBuff[1] & 0xe0) >> 3;
			unsigned char b = (sourceBuff[0] & 0xc0) >> 6;

			destBuff[0] = (r | g | b);

			sourceBuff += 4;
			destBuff += 1;
		}
	}

	void ImageUtils::convertR8G8B8toR8G8B8(const void* source, int pixelCount, void* dest){
		memcpy(dest, source, pixelCount * 3);
	}

	void ImageUtils::convertR8G8B8toA8R8G8B8(const void* source, int pixelCount, void* dest){
		unsigned char*  sourceBuff = (unsigned char*)source;
		unsigned int* destBuff = (unsigned int*)dest;

		for (int x = 0; x < pixelCount; x++){
			*destBuff = 0xff000000 | (sourceBuff[0] << 16) | (sourceBuff[1] << 8) | sourceBuff[2];

			sourceBuff += 3;
			++destBuff;
		}
	}

	void ImageUtils::convertR8G8B8toA1R5G5B5(const void* source, int pixelCount, void* dest){
		unsigned char * sourceBuff = (unsigned char *)source;
		unsigned short* destBuff = (unsigned short*)dest;

		for (int x = 0; x < pixelCount; x++){
			int r = sourceBuff[0] >> 3;
			int g = sourceBuff[1] >> 3;
			int b = sourceBuff[2] >> 3;

			destBuff[0] = (0x8000) | (r << 10) | (g << 5) | (b);

			sourceBuff += 3;
			destBuff += 1;
		}
	}

	void ImageUtils::convertR8G8B8toR5G6B5(const void* source, int pixelCount, void* dest){
		unsigned char*  sourceBuff = (unsigned char*)source;
		unsigned int* destBuff = (unsigned int*)dest;

		for (int x = 0; x < pixelCount; x++){
			*destBuff = 0xff000000 | (sourceBuff[2] << 16) | (sourceBuff[1] << 8) | sourceBuff[0];

			sourceBuff += 3;
			++destBuff;
		}
	}

	void ImageUtils::convertB8G8R8toA8R8G8B8(const void* source, int pixelCount, void* dest){
		unsigned char* sourceBuff = (unsigned char*)source;
		unsigned char* destBuff = (unsigned char*)dest;

		for (int x = 0; x < pixelCount; x++){
			destBuff[0] = sourceBuff[3];
			destBuff[1] = sourceBuff[2];
			destBuff[2] = sourceBuff[1];
			destBuff[3] = sourceBuff[0];

			sourceBuff += 4;
			destBuff += 4;
		}
	}

	void ImageUtils::convertB8G8R8A8toA8R8G8B8(const void* source, int pixelCount, void* dest){
		unsigned char * sourceBuff = (unsigned char *)source;
		unsigned short* destBuff = (unsigned short*)dest;

		for (int x = 0; x < pixelCount; x++){
			int r = sourceBuff[0] >> 3;
			int g = sourceBuff[1] >> 2;
			int b = sourceBuff[2] >> 3;

			destBuff[0] = (r << 11) | (g << 5) | (b);

			sourceBuff += 3;
			destBuff += 1;
		}
	}

	void ImageUtils::convertR5G6B5toR5G6B5(const void* source, int pixelCount, void* dest){
		memcpy(dest, source, pixelCount * 2);
	}

	void ImageUtils::convertR5G6B5toR8G8B8(const void* source, int pixelCount, void* dest){
		unsigned short* sourceBuff = (unsigned short*)source;
		unsigned char * destBuff = (unsigned char *)dest;

		for (int x = 0; x < pixelCount; x++){
			destBuff[0] = (*sourceBuff & 0xf800) >> 8;
			destBuff[1] = (*sourceBuff & 0x07e0) >> 3;
			destBuff[2] = (*sourceBuff & 0x001f) << 3;

			sourceBuff += 1;
			destBuff += 3;
		}
	}

	void ImageUtils::convertR5G6B5toB8G8R8(const void* source, int pixelCount, void* dest){
		unsigned short* sourceBuff = (unsigned short*)source;
		unsigned char * destBuff = (unsigned char *)dest;

		for (int x = 0; x < pixelCount; x++){
			destBuff[2] = (*sourceBuff & 0xf800) >> 8;
			destBuff[1] = (*sourceBuff & 0x07e0) >> 3;
			destBuff[0] = (*sourceBuff & 0x001f) << 3;

			sourceBuff += 1;
			destBuff += 3;
		}
	}

	void ImageUtils::convertR5G6B5toA8R8G8B8(const void* source, int pixelCount, void* dest){
		unsigned short* sourceBuff = (unsigned short*)source;
		unsigned int* destBuff = (unsigned int*)dest;

		for (int x = 0; x < pixelCount; x++)
			*destBuff++ = Graphics::ColorUtils::fromR5G6B5toA8R8G8B8(*sourceBuff++);
	}

	void ImageUtils::convertR5G6B5toA1R5G5B5(const void* source, int pixelCount, void* dest){
		unsigned short* sourceBuff = (unsigned short*)source;
		unsigned short* destBuff = (unsigned short*)dest;

		for (int x = 0; x < pixelCount; x++)
			*destBuff++ = Graphics::ColorUtils::fromR5G6B5toA1R5G5B5(*sourceBuff++);
	}

	void ImageUtils::convert(const void* source, Graphics::EColorFormat sourceFormat, int pixelCount, void* dest, Graphics::EColorFormat destFormat){
		switch (sourceFormat){
		case Graphics::EColorFormat::A1R5G5B5:
			switch (destFormat){
			case Graphics::EColorFormat::A1R5G5B5:
				convertA1R5G5B5toA1R5G5B5(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::R5G6B5:
				convertA1R5G5B5toR5G6B5(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::A8R8G8B8:
				convertA1R5G5B5toA8R8G8B8(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::R8G8B8:
				convertA1R5G5B5toR8G8B8(source, pixelCount, dest);
				break;
			default:
				break;
			} break;
		case Graphics::EColorFormat::R5G6B5:
			switch (destFormat){
			case Graphics::EColorFormat::A1R5G5B5:
				convertR5G6B5toA1R5G5B5(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::R5G6B5:
				convertR5G6B5toR5G6B5(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::A8R8G8B8:
				convertR5G6B5toA8R8G8B8(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::R8G8B8:
				convertR5G6B5toR8G8B8(source, pixelCount, dest);
				break;
			default:
				break;
			} break;
		case Graphics::EColorFormat::A8R8G8B8:
			switch (destFormat){
			case Graphics::EColorFormat::A1R5G5B5:
				convertA8R8G8B8toA1R5G5B5(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::R5G6B5:
				convertA8R8G8B8toR5G6B5(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::A8R8G8B8:
				convertA8R8G8B8toA8R8G8B8(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::R8G8B8:
				convertA8R8G8B8toR8G8B8(source, pixelCount, dest);
				break;
			default:
				break;
			} break;
		case Graphics::EColorFormat::R8G8B8:
			switch (destFormat){
			case Graphics::EColorFormat::A1R5G5B5:
				convertR8G8B8toA1R5G5B5(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::R5G6B5:
				convertR8G8B8toR5G6B5(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::A8R8G8B8:
				convertR8G8B8toA8R8G8B8(source, pixelCount, dest);
				break;
			case Graphics::EColorFormat::R8G8B8:
				convertR8G8B8toR8G8B8(source, pixelCount, dest);
				break;
			default:
				break;
			} break;
		}
	}




} }