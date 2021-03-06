// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef UITHEMEMANAGER_HPP
# define UITHEMEMANAGER_HPP

/*!
 * \file UIThemeManager.hpp
 * \brief Détenteur du thème d'UI, applicable par tous les autres components d'ui.
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStartUI.hpp"

namespace Game
{
	namespace Component
	{
		class UIThemeManager : public BeerEngine::Component::Component, 
								public BeerEngine::Component::IStart,
								public BeerEngine::Component::IStartUI,
								public BeerEngine::Component::IUI
		{
		private:
			UIThemeManager();
			UIThemeManager(const UIThemeManager &val);
			UIThemeManager & operator=( UIThemeManager const & rhs );

		public:

			nk_style_window defaultWindow;
			nk_style_button defaultButton;
			nk_style_property defaultProperty;
			nk_style_text defaultText;
			nk_style_slider defaultSlider;

			std::map<std::string, nk_font *> available_fonts;

			nk_style_button themeButton;

			UIThemeManager(BeerEngine::GameObject *gameObject);
			virtual ~UIThemeManager( void );

			friend std::ostream & operator<<(std::ostream & o, UIThemeManager const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);
	
			void saveDefaultUI(struct nk_context *ctx);
			void setThemeUI(struct nk_context *ctx);
			void resetToDefaultUI(struct nk_context *ctx);

			nk_style_item loadSprite(std::string spritePath);

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
