#pragma once

#include "../../Graphics/Textures/ITexture.h"
#include "../../Graphics/Textures/Image.h"
#include "../../Graphics/Colors/Color.h"

namespace Derpy { namespace Assets {

	class AssetManager{
	public:
		static Graphics::Image* createImage(unsigned int& width, unsigned int& height, Graphics::EColorFormat format);
		static bool getTextureCreationFlag(Graphics::ETextureCreationFlag flag);
	};


} }