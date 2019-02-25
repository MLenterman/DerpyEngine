#pragma once

#include <iostream>
#include <vector>
#include <glew.h>

#include "../../Maths/Maths.h"
#include "../../Utils/File_Utils.h"

namespace Derpy { namespace Graphics {

	class Shader{
	private:
		const char* m_VertPath;
		const char* m_FragPath;
	public:
		GLuint m_ShaderID;
		Shader(const char* vertPath, const char* fragPath);
		~Shader();


		void setUniform1f(const GLchar* name, float value);
		void setUniform1fv(const GLchar* name, float* value, int count);
		void setUniform1i(const GLchar* name, int value);
		void setUniform1iv(const GLchar* name, int* value, int count);
		void setUniform2f(const GLchar* name, const Maths::Vec2f& vector);
		void setUniform3f(const GLchar* name, const Maths::Vec3f& vector);
		void setUniform4f(const GLchar* name, const Maths::Vec4f& vector);
		void setUniformMat4(const GLchar* name, const Maths::Mat4f& matrix);

		void enable() const;
		void disable() const;
	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);
	};

} }