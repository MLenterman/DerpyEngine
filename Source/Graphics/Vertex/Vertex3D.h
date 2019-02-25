#pragma once

#include "../../Maths/Maths.h"
#include "../../Graphics/Colors/Color.h"

namespace Derpy { namespace Graphics {

	enum class VertexType{
		NORMAL,
		DUAL_TEXTURE,
		TANGENT
	};

	struct Vertex3D{

		Maths::Vec3f position;
		Maths::Vec3f normal;
		Color color;
		Maths::Vec2f textureCoords;

		Vertex3D();
		Vertex3D(const float posX, float posY, float posZ, float normalX, float normalY, float normalZ, 
			Color color, float textureU, float textureV);
		Vertex3D(const Maths::Vec3f& pos, const Maths::Vec3f& normal, Color color, const Maths::Vec2f& textureCoords);
		~Vertex3D();

		bool operator==(const Vertex3D& other) const;
		bool operator!=(const Vertex3D& other) const;

		VertexType getType() const;
		Vertex3D getInterpolated(const Vertex3D& other, float d);
		

	};


} }