#include "Core/Graphics/AMaterial.hpp"
#include "Core/Window.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		AMaterial::AMaterial(ShaderProgram *shader, glm::vec4 color) :
			_shader(shader),
			_color(color)
		{
			shader->bind();
			_projectionShaderID = _shader->getUniformLocation("projection");
			_viewShaderID = _shader->getUniformLocation("view");
			_modelShaderID = _shader->getUniformLocation("model");
			_colorShaderID = _shader->getUniformLocation("color");
		}

		void	AMaterial::bind(glm::mat4 &model)
		{
			static glm::mat4 identity(1.0f);
			_shader->bind();
			_shader->uniformMat(_projectionShaderID, Window::GetInstance()->getProjection3D());
			_shader->uniformMat(_viewShaderID, identity);
			_shader->uniformMat(_modelShaderID, model);
			_shader->uniform4f(_colorShaderID, _color[0], _color[1], _color[2], _color[3]);
		}

		AMaterial		&AMaterial::setColor(glm::vec4 color)
		{
			_color = color;
			return (*this);
		}
	}
}