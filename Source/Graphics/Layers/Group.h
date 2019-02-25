#pragma once

#include "../Rendering/Renderable2D.h"

namespace Derpy { namespace Graphics {

	class Group : public Renderable2D{
	private:
		std::vector<Renderable2D*> m_Renderables;
		Maths::Mat4f m_TransformationMatrix;
	public:
		Group(const Maths::Mat4f& transform);
		~Group();
		void add(Renderable2D* renderable);
		void submit(Renderer2D* renderer) const override;
	};

} }