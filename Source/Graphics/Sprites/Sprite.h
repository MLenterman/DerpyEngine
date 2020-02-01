#pragma once

#include "../Rendering/Renderable2D.h"

namespace Derpy { namespace Graphics {

	class Sprite : public Renderable2D{
	public:
		Maths::Vec3f& position;
	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, ITexture* texture);
	};

} }