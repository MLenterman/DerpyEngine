#pragma once

#include <vector>
#include <glew.h>

//#include "font.h"
#include "../../Maths/Maths.h"


namespace Derpy { namespace Graphics {

	class Renderable2D;

	class Renderer2D{
	protected:
		std::vector<Maths::Mat4f> m_TransformationStack;
		const Maths::Mat4f* m_TransformationBack;
	protected:
		Renderer2D(){
			m_TransformationStack.push_back(Maths::Mat4f::identity());
			m_TransformationBack = &m_TransformationStack.back();
		}
	public:
		virtual ~Renderer2D() { }
		void push(const Maths::Mat4f& matrix, bool override = false){
			if (override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

			m_TransformationBack = &m_TransformationStack.back();
		}
		void pop(){
			// TODO: Add to log!
			if (m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();

			m_TransformationBack = &m_TransformationStack.back();
		}

		virtual void begin() {}
		virtual void submit(const Renderable2D* renderable) = 0;
		//virtual void drawString(const std::string& text, const Maths::Vec3f& position, const Font& font, unsigned int color) { }
		virtual void end() {}
		virtual void flush() = 0;
	};

} }