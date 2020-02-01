#include "Texture_GL.h"

namespace Derpy { namespace Graphics {
	Texture_GL::Texture_GL(const char* textureName, Image* image, void* mipmapData, Assets::AssetManager* manager)
		: ITexture(textureName), m_ColorFormat(EColorFormat::A8R8G8B8), m_AssetManager(manager), m_Image(NULL), m_MipMapImage(NULL),
			m_TextureId(0), m_InternalFormat(GL_RGBA), m_PixelFormat(GL_BGRA_EXT),
			m_PixelType(GL_UNSIGNED_BYTE), m_MipLevelStored(0), m_IsRenderTarget(false),
			m_AutomaticMipmapUpdate(false), m_KeepImage(true){

		m_HasMipMaps = m_AssetManager->getTextureCreationFlag(ETextureCreationFlag::CREATE_MIP_MAPS);
		getImageValues(image);

		glGenTextures(1, &m_TextureId);

		if (m_ImageWidth == m_TextureWidth && m_ImageHeight == m_TextureHeight){
			m_Image = m_AssetManager->createImage(m_ImageWidth, m_ImageWidth, m_ColorFormat);
			image->copyTo(m_Image); // TODO: DETACH IMAGE COPY FUNCTIONS TO HELPER CLASS
		}
		else{
			m_Image = m_AssetManager->createImage(m_TextureWidth, m_TextureHeight, m_ColorFormat);
			image->copyToScaling(m_Image); // TODO: DETACH IMAGE COPY FUNCTIONS TO HELPER CLASS
		}

		uploadTexture(true, mipmapData);

		if (!m_KeepImage){
			delete m_Image;
			m_Image = NULL;
		}

	}

	Texture_GL::Texture_GL(const char* textureName, Assets::AssetManager* manager)
		: ITexture(textureName), m_ColorFormat(EColorFormat::A8R8G8B8), m_AssetManager(manager), m_Image(NULL), m_MipMapImage(NULL),
		m_TextureId(0), m_InternalFormat(GL_RGBA), m_PixelFormat(GL_BGRA_EXT),
		m_PixelType(GL_UNSIGNED_BYTE), m_MipLevelStored(0), m_IsRenderTarget(false),
		m_AutomaticMipmapUpdate(false){

	}

	Texture_GL::~Texture_GL(){

	}

	System::EGraphicsDriver Texture_GL::getDriverType() const{
		return System::EGraphicsDriver::OPENGL;
	}

	void* Texture_GL::lock(ETextureLockMode mode, unsigned int mipmapLevel){
		return NULL;
	}

	void Texture_GL::unlock(){
		
	}

	void Texture_GL::getOriginalSize(int& width, int& height) const{

	}

	void Texture_GL::getSize(int& width, int& height) const{

	}

	EColorFormat Texture_GL::getColorFormat() const{
		return EColorFormat::A1R5G5B5;
	}

	bool Texture_GL::hasAlpha() const{
		return false;
	}

	bool Texture_GL::hasMipMaps() const{
		return false;
	}

	void Texture_GL::regenerateMipMapLevels(void* mipmapData){

	}

	bool Texture_GL::isRenderTarget() const{
		return false;
	}

	void Texture_GL::setIsRenderTarget(bool isTarget){

	}

	bool Texture_GL::isFrameBufferObject() const{
		return false;
	}

	void Texture_GL::bindRenderTargetTexture(){

	}

	void Texture_GL::unbindRenderTargetTexture(){

	}

	GLuint Texture_GL::getOpenGLTextureName() const{
		return 0;
	}

	void Texture_GL::getImageValues(Image* image){
		image->getDimensions(m_ImageWidth, m_ImageHeight);

		if (!m_ImageWidth || !m_ImageHeight){
			// LOG
			return;
		}

		const float ratio = (float)m_ImageWidth / (float)m_ImageHeight;

		if ((m_ImageWidth > DERPY_TEXTURES_MAX_SIZE) && (ratio >= 1.0f)){
			m_ImageWidth = DERPY_TEXTURES_MAX_SIZE;
			m_ImageHeight = (unsigned int)(DERPY_TEXTURES_MAX_SIZE / ratio);
		}
		else if (m_ImageHeight > DERPY_TEXTURES_MAX_SIZE){
			m_ImageHeight = DERPY_TEXTURES_MAX_SIZE;
			m_ImageWidth = (unsigned int)(DERPY_TEXTURES_MAX_SIZE * ratio);
		}

		m_TextureWidth = m_ImageWidth;
		m_TextureHeight = m_ImageHeight;
		m_ColorFormat = image->getColorFormat(); // TODO: IMPLEMENT TEXTURE CREATION FLAG FOR OPTIMIZING
	}

	void Texture_GL::uploadTexture(bool newTexture, void* mipmapData, unsigned int mipLevel){

	}

} }