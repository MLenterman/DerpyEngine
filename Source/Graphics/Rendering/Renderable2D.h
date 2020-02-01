#pragma once

#include "../Buffers/Buffer.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"

#include "Renderer2D.h"
#include "../Textures/ITexture.h"

#include "../../Maths/Maths.h"
#include "../Shaders/Shader.h"

namespace Derpy { namespace Graphics {

	struct VertexData{
		Maths::Vec3f vertex;
		Maths::Vec2f uv;
		float tid;
		unsigned int color;
	};

	class Renderable2D{
	protected:
		Maths::Vec3f m_Position;
		Maths::Vec2f m_Size;
		unsigned int m_Color;
		std::vector<Maths::Vec2f> m_UV;
		ITexture* m_Texture;
	protected:
		Renderable2D() : m_Texture(nullptr) { setUVDefaults(); }
	public:
		Renderable2D(Maths::Vec3f position, Maths::Vec2f size, unsigned int color)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr){
			setUVDefaults();
		}

		virtual ~Renderable2D() { }

		virtual void submit(Renderer2D* renderer) const{
			renderer->submit(this);
		}

		void setColor(unsigned int color) { m_Color = color; }
		void setColor(const Maths::Vec4f& color){
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			m_Color = a << 24 | b << 16 | g << 8 | r;
		}

		inline const Maths::Vec3f& getPosition() const { return m_Position; }
		inline const Maths::Vec2f& getSize() const { return m_Size; }
		inline const unsigned int getColor() const { return m_Color; }
		inline const std::vector<Maths::Vec2f>& getUV() const { return m_UV; }

		inline const GLuint getTID() const { return m_Texture ? m_Texture->getID() : 0; }
	private:
		void setUVDefaults(){
			m_UV.push_back(Maths::Vec2f(0, 0));
			m_UV.push_back(Maths::Vec2f(0, 1));
			m_UV.push_back(Maths::Vec2f(1, 1));
			m_UV.push_back(Maths::Vec2f(1, 0));
		}
	};

} }