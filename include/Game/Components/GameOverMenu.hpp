// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef GAMEOVERMENU_HPP
# define GAMEOVERMENU_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IEnable.hpp"

namespace Game
{
	namespace Component
	{
		class GameOverMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI,
						public BeerEngine::Component::IEnable
		{
		public:
			UIThemeManager	*uiManager;
			nk_style_item	backgroundImage;
			nk_style_item	youLoseImage;

			// GameOverMenu( void );
			// GameOverMenu( GameOverMenu const & src );
			GameOverMenu(BeerEngine::GameObject *gameObject);

			virtual ~GameOverMenu( void );

			GameOverMenu & operator=( GameOverMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, GameOverMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);
			virtual void enable();
			
			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif