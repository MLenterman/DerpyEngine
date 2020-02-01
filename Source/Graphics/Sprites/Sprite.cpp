#include "Sprite.h"

namespace Derpy { namespace Graphics {

	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		: Renderable2D(Maths::Vec3f(x, y, 0), Maths::Vec2f(width, height), color), position(m_Position){

	}

	Sprite::Sprite(float x, float y, float width, float height, ITexture* texture)
		: Renderable2D(Maths::Vec3f(x, y, 0), Maths::Vec2f(width, height), 0xffffffff), position(m_Position){
		m_Texture = texture;
	}

} }