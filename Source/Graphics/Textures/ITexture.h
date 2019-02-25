#pragma once

#include "../Colors/Color.h"
#include "../../System/GraphicsDriver.h"

namespace Derpy { namespace Graphics {

	enum class ETextureCreationFlag{
		ALWAYS_16_BIT = 0x00000001,
		ALWAYS_32_BIT = 0x00000002,
		OPTIMIZED_FOR_QUALITY = 0x00000004,
		OPTIMIZED_FOR_SPEED = 0x00000008,
		CREATE_MIP_MAPS = 0x00000010,
		NO_ALPHA_CHANNEL = 0x00000020,
		ALLOW_NON_POWER_2 = 0x00000040,
	};

	enum class ETextureLockMode{
		READ_WRITE,
		READ_ONLY,
		WRITE_ONLY
	};

	class ITexture{
	protected:
		const char* m_TextureName;

	public:
		ITexture(const char* textureName) : m_TextureName(textureName){

		}
		
		virtual System::EGraphicsDriver getDriverType() const = 0;

		virtual void* lock(ETextureLockMode mode = ETextureLockMode::READ_WRITE, unsigned int mipmapLevel = 0) = 0;
		virtual void unlock() = 0;

		virtual void getOriginalSize(int& width, int& height) const = 0;
		virtual void getSize(int& width, int& height) const = 0;

		
		virtual EColorFormat getColorFormat() const = 0;

		virtual bool hasAlpha() const {
			return getColorFormat() == EColorFormat::A8R8G8B8 || getColorFormat() == EColorFormat::A1R5G5B5;
		}

		virtual bool hasMipMaps() const { return false; }
		virtual void regenerateMipMapLevels(void* mipmapData = 0) = 0;

		virtual bool isRenderTarget() const { return false; }

		const char* getTextureName() const { return m_TextureName; }

	protected:
		ITexture() { }

		inline ETextureCreationFlag getTextureFormatFromFlags(unsigned int flags){
			if (flags & (unsigned int)ETextureCreationFlag::OPTIMIZED_FOR_SPEED)
				return ETextureCreationFlag::OPTIMIZED_FOR_SPEED;
			if (flags & (unsigned int)ETextureCreationFlag::ALWAYS_16_BIT)
				return ETextureCreationFlag::ALWAYS_16_BIT;
			if (flags & (unsigned int)ETextureCreationFlag::ALWAYS_32_BIT)
				return ETextureCreationFlag::ALWAYS_32_BIT;
			if (flags & (unsigned int)ETextureCreationFlag::OPTIMIZED_FOR_QUALITY)
				return ETextureCreationFlag::OPTIMIZED_FOR_QUALITY;

			return ETextureCreationFlag::OPTIMIZED_FOR_SPEED;
		}

		
	};


} }