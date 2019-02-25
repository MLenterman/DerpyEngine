#pragma once

#include <glew.h>

namespace Derpy { namespace Graphics {

	enum class BufferType{
		NONE,
		VERTEX,
		INDEX,
		VERTEX_AND_INDEX
	};

	enum class IndexType{
		BITS16,
		BITS32
	};

	class Buffer{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;
	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
		~Buffer();
		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return m_ComponentCount; }
	};

} }