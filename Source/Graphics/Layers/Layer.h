#pragma once

#include "../Rendering/Renderer2D.h"
#include "../Rendering/Renderable2D.h"

namespace Derpy { namespace Graphics {

	class Layer{
	protected:
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;
		Maths::Mat4f m_ProjectionMatrix;
	public:
		Layer(Renderer2D* renderer, Shader* shader, Maths::Mat4f projectionMatrix);
		virtual ~Layer();
		virtual void add(Renderable2D* renderable);
		virtual void render();

		inline const std::vector<Renderable2D*>& getRenderables() const { return m_Renderables; }
	};

} }