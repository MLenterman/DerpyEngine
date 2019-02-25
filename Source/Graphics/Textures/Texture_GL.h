#pragma once

#include <glew.h>

#include "ITexture.h"
#include "Image.h"
#include "../../Assets/AssetManager.h"

namespace Derpy { namespace Graphics{

#define DERPY_TEXTURES_MAX_SIZE 2048

	class Texture_GL : public ITexture{
	protected:
		GLuint m_TextureId;
		EColorFormat m_ColorFormat;
		GLint m_InternalFormat;
		GLenum m_PixelFormat;
		GLenum m_PixelType;
		unsigned int m_ImageWidth, m_ImageHeight;
		unsigned int m_TextureWidth, m_TextureHeight;

		Image* m_Image;
		Image* m_MipMapImage;

		Assets::AssetManager* m_AssetManager;

		unsigned char m_MipLevelStored;
		bool m_HasMipMaps;
		bool m_IsRenderTarget;
		bool m_AutomaticMipmapUpdate;
		bool m_KeepImage;

	public:
		Texture_GL(const char* textureName, Image* image, void* mipmapData = NULL, Assets::AssetManager* manager = NULL);
		~Texture_GL();

		virtual System::EGraphicsDriver getDriverType() const;

		virtual void* lock(ETextureLockMode mode = ETextureLockMode::READ_WRITE, unsigned int mipmapLevel = 0);
		virtual void unlock();

		virtual void getOriginalSize(int& width, int& height) const;
		virtual void getSize(int& width, int& height) const;

		virtual EColorFormat getColorFormat() const;

		virtual bool hasAlpha() const;

		virtual bool hasMipMaps() const;
		virtual void regenerateMipMapLevels(void* mipmapData = 0);

		virtual bool isRenderTarget() const;
		void setIsRenderTarget(bool isTarget);
		virtual bool isFrameBufferObject() const;
		virtual void bindRenderTargetTexture();
		virtual void unbindRenderTargetTexture();

		GLuint getOpenGLTextureName() const;
	protected:
		Texture_GL(const char* textureName, Assets::AssetManager* manager = NULL);

		void getImageValues(Image* image);
		void uploadTexture(bool newTexture = false, void* mipmapData = NULL, unsigned int mipLevel = 0);
	};

} }