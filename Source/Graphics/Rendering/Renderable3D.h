#pragma once

#include "../Buffers/Buffer.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"

#include "../Textures/ITexture.h"

#include "../../Maths/Maths.h"
#include "../Shaders/Shader.h"

	/*
namespace Derpy { namespace Graphics {
	class Renderable3D{
	protected:
		std::vector<Maths::Vec3f> m_Vertices;
		std::vector<Maths::Vec2f> m_TextureCoordinates;
		std::vector<Maths::Vec3f> m_Normals;
		//std::vector<Face> faces;
		//HashMap<String, Material> materials = new HashMap<String, Material>();
		bool m_EnableSmoothShading;
	protected:
		Renderable3D() : m_Texture(nullptr) { setUVDefaults(); }
	public:
		Renderable3D(Maths::Vec3f position, Maths::Vec3f size, unsigned int color)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr){
			setUVDefaults();
		}

		virtual ~Renderable3D() { }

		virtual void submit(Renderer3D* renderer) const{
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
		inline const Maths::Vec3f& getSize() const { return m_Size; }
		inline const unsigned int getColor() const { return m_Color; }
		inline const std::vector<Maths::Vec3f>& getUV() const { return m_UV; }

		inline const GLuint getTID() const { return m_Texture ? m_Texture->getID() : 0; }

		inline void addVertex(const Maths::Vec3f& vertex){ m_Vertices.push_back(vertex); }
		inline void addTextureCoordinate(const Maths::Vec2f& textureCoordinate){ m_TextureCoordinates.push_back(textureCoordinate); }
		inline void addNormal(const Maths::Vec3f& normal){ m_Normals.push_back(normal); }
	private:
		void setUVDefaults(){
			m_UV.push_back(Maths::Vec3f(0, 0, 0));
			m_UV.push_back(Maths::Vec3f(0, 1, 0));
			m_UV.push_back(Maths::Vec3f(1, 1, 0));
			m_UV.push_back(Maths::Vec3f(1, 0, 0));
		}
	};


} }
*/