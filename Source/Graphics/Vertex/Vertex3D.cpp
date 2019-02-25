#include "Vertex3D.h"

namespace Derpy { namespace Graphics {

	Vertex3D::Vertex3D(){

	}

	Vertex3D::Vertex3D(const float posX, float posY, float posZ, float normalX, float normalY, float normalZ,
		Color color, float textureU, float textureV)
		: position(posX, posY, posZ), normal(normalX, normalY, normalZ), color(color), textureCoords(textureU, textureV){

	}

	Vertex3D::Vertex3D(const Maths::Vec3f& pos, const Maths::Vec3f& normal, Color color, const Maths::Vec2f& textureCoords) 
		: position(pos), normal(normal), color(color), textureCoords(textureCoords){

	}

	bool Vertex3D::operator==(const Vertex3D& other) const{
		return position == other.position && normal == other.normal && 
			color == other.color && textureCoords == other.textureCoords;
	}

	bool Vertex3D::operator!=(const Vertex3D& other) const{
		return position != other.position || normal != other.normal || 
			color != other.color || textureCoords != other.textureCoords;
	}

	VertexType Vertex3D::getType() const{
		return VertexType::NORMAL;
	}

	Vertex3D Vertex3D::getInterpolated(const Vertex3D& other, float d){
		d = Maths::clamp(d, 0.0f, 1.0f);
		
		return Vertex3D(
			position.getInterpolated(other.position, d),
			normal.getInterpolated(other.normal, d),
			color.getInterpolated(other.color, d),
			textureCoords.getInterpolated(other.textureCoords, d));
	}

} }