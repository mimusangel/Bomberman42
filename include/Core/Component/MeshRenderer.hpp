#ifndef BE_CORE_COMPONENT_MESHRENDERER_HPP
#define BE_CORE_COMPONENT_MESHRENDERER_HPP 1

#include "Core/Core.hpp"
#include "Component.hpp"
#include "IRenderForward.hpp"
#include "Core/Graphics/Lights/ALight.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class MeshRenderer : public Component, public IRenderForward
		{
		protected:
			Graphics::Mesh		*_mesh;
			Graphics::AMaterial	*_material;
			glm::mat4			_mat;
			std::string			_sourceFile;

		public:
			MeshRenderer(GameObject *gameObject);
			Graphics::Mesh	*getMesh(void);
			MeshRenderer	&setMesh(Graphics::Mesh *mesh);
			MeshRenderer	&setMesh(std::string inputfile);	
			Graphics::AMaterial	*getMaterial(void);
			MeshRenderer	&setMaterial(Graphics::AMaterial *material);

			virtual void    renderUpdate(void);
			virtual void    render(BeerEngine::Graphics::ALight &light);

			GLenum 			renderMode;

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
