#include "Game/Components/VersusMenu.hpp"
#include "Game/Components/MainMenu.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Window.hpp"
#include "Core/SceneManager.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*VersusMenu::VersusMenu ( void )
{
	return ;
}*/

/*VersusMenu::VersusMenu ( VersusMenu const & src )
{
	*this = src;
	return ;
}*/

VersusMenu &				VersusMenu::operator=( VersusMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

VersusMenu::~VersusMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

VersusMenu::VersusMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, VersusMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void VersusMenu::start()
{
	std::cout << "VersusMenu start" << std::endl;
	maps.push_back({"level 1", "assets/scenes/level1.scene"});
	maps.push_back({"level 2", "assets/scenes/level2.scene"});
	maps.push_back({"level 3", "assets/scenes/level3.scene"});
}

void VersusMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	
}

void VersusMenu::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);

	float menuWidth = 320;
	float menuHeight = 375 + 5 * 10;
	float xOffset = 0;
	float yOffset = 100;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	ctx->style.window.spacing = nk_vec2(0, 10);
	if (nk_begin(ctx, "Versus", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 75, 1);

		for (auto it = maps.begin(); it != maps.end(); it++)
		{
			if (nk_button_label(ctx, it->name.c_str()))
				BeerEngine::SceneManager::LoadScene(it->scenePath);
		}
		if (nk_button_label(ctx, "Random"))
		{
			// TODO
		}
		if (nk_button_label(ctx, "Back"))
		{
			this->setActive(false);
			mainMenu->setActive(true);
		}
	}
	nk_end(ctx);

	uiManager->resetToDefaultUI(ctx);
}

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
	}
}