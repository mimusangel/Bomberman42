#ifndef BE_CORE_GRAPHICS_AMATERIAL_HPP
#define BE_CORE_GRAPHICS_AMATERIAL_HPP 1

#include "ShaderProgram.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class AMaterial
		{
		private:
			ShaderProgram	*_shader;
			glm::vec4		_color;

			// ID
			GLint	_colorShaderID;
			GLint	_projectionShaderID;
			GLint	_viewShaderID;
			GLint	_modelShaderID;
		
		public:
			AMaterial(ShaderProgram *shader, glm::vec4 color = glm::vec4(1.0f));
			virtual ~AMaterial() {};
			virtual void	bind(glm::mat4 &model);
			AMaterial		&setColor(glm::vec4 color);
		};
	}
}

#endif