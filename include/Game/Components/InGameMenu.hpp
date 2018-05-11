// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef INGAMEMENU_HPP
# define INGAMEMENU_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IUI.hpp"

namespace Game
{
	namespace Component
	{

		class InGameMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IStartUI,
						public BeerEngine::Component::IUI
		{
		public:
			UIThemeManager	*uiManager;

			// InGameMenu( void );
			// InGameMenu( InGameMenu const & src );
			InGameMenu(BeerEngine::GameObject *gameObject);

			virtual ~InGameMenu( void );

			InGameMenu & operator=( InGameMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, InGameMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void setUI(struct nk_context *ctx);
	
		};

	};

};

#endif