#define NK_INCLUDE_FONT_BAKING

#include "Game/Components/SettingsMenu.hpp"
#include "Game/Components/Settings.hpp"
#include "Game/Components/MainMenu.hpp"
#include "Game/Components/InputsMenu.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Window.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*SettingsMenu::SettingsMenu ( void )
{
	return ;
}*/

/*SettingsMenu::SettingsMenu ( SettingsMenu const & src )
{
	*this = src;
	return ;
}*/

SettingsMenu &				SettingsMenu::operator=( SettingsMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

SettingsMenu::~SettingsMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

SettingsMenu::SettingsMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, SettingsMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void SettingsMenu::start()
{
	std::cout << "SettingsMenu start" << std::endl;
	// windowHeight = WINDOW_HEIGHT;
	// windowWidth = WINDOW_WIDTH;
	musicVolume = 50.0f;
	soundVolume = 50.0f;
}

void SettingsMenu::setUI(struct nk_context *ctx)
{
	ctx->style.window = mWindow;
	ctx->style.text.color = nk_rgb(255,255,255);
	ctx->style.slider.bar_normal = nk_rgb(255,255,255);
	ctx->style.slider.bar_hover = nk_rgb(200,200,200);
	ctx->style.slider.bar_filled = nk_rgb(0,0,0);
	ctx->style.option.text_normal = nk_rgb(255,255,255);
	ctx->style.option.active = nk_style_item_color(nk_rgb(255,255,255));
	ctx->style.option.normal = nk_style_item_color(nk_rgb(255,255,255));
	ctx->style.option.hover = nk_style_item_color(nk_rgb(255,255,255));
	// ctx->style.window.spacing = nk_vec2(0, 0);
	// nk_style_set_font(ctx, &uiManager->available_fonts["smallMain"]->handle);
}

void SettingsMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	std::cout << "start UI settings menu" << std::endl;
	mWindow = uiManager->defaultWindow;

	mWindow.fixed_background = nk_style_item_hide();
	// mWindow.padding = nk_vec2(0, 0);
	mWindow.spacing = nk_vec2(0, 10);
}

void SettingsMenu::saveSettings()
{
	settingsManager->saveSettings();
}

void SettingsMenu::resetSettings()
{
	settingsManager->resetSettings();
	inputsMenu->updateDisplayedInputKeys();
}

void SettingsMenu::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	setUI(ctx);
	float menuWidth = 640;
	float menuHeight = 375 + 5 * 10;
	float xOffset = 150;
	float yOffset = 100;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	if (nk_begin(ctx, "Settings", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 50, 2);

		mode = BeerEngine::Window::GetInstance()->isFullScreen() ? FULL_SCREEN : WINDOWED;

		std::stringstream ssHeight;
		ssHeight << "Height: " << windowHeight;
		windowHeight = BeerEngine::Window::GetInstance()->getHeight();
		int height = windowHeight;
		nk_label(ctx, ssHeight.str().c_str(), NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &windowHeight, 1440.0f, 10.0f);

		std::stringstream ssWidth;
		ssWidth << "Width: " << windowWidth;
		windowWidth = BeerEngine::Window::GetInstance()->getWidth();
		int width = windowWidth;
		nk_label(ctx, ssWidth.str().c_str(), NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &windowWidth, 2560.0f, 10.0f);

		if (width != static_cast<int>(windowWidth) || height != static_cast<int>(windowHeight))
			BeerEngine::Window::GetInstance()->resize(windowWidth, windowHeight);
		if (nk_option_label(ctx, "windowed", mode == WINDOWED))
		{
			if (mode != WINDOWED)
				BeerEngine::Window::GetInstance()->setWindowed();
			mode = WINDOWED;
		}
    	if (nk_option_label(ctx, "full screen", mode == FULL_SCREEN))
		{
			if (mode != FULL_SCREEN)
				BeerEngine::Window::GetInstance()->setFullScreen();
			mode = FULL_SCREEN;
		}

		std::stringstream ssMusic;
		ssMusic << "Music volume: " << musicVolume;
		nk_label(ctx, ssMusic.str().c_str(), NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &musicVolume, 100.0f, 1.0f);

		std::stringstream ssSound;
		ssSound << "Sound volume: " << soundVolume;
		nk_label(ctx, ssSound.str().c_str(), NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &soundVolume, 100.0f, 1.0f);

		uiManager->setThemeUI(ctx);
		ctx->style.window.spacing = nk_vec2(10, 0);

		nk_layout_row_dynamic(ctx, 75, 3);
		if (nk_button_label(ctx, "Inputs"))
		{
			this->setActive(false);
			inputsMenu->setActive(true);
		}
		if (nk_button_label(ctx, "Reset"))
		{
			this->resetSettings();
		}
		if (nk_button_label(ctx, "Back"))
		{
			saveSettings();
			this->setActive(false);
			mainMenu->setActive(true);
		}

		// // centered buttons
		// nk_layout_row_begin(ctx, NK_STATIC, 150 + 10 * 2, 2);

		// // empty column to center buttons
		// nk_layout_row_push(ctx, (640 - 320) / 2);
		// if (nk_group_begin(ctx, "column1", NK_WINDOW_NO_SCROLLBAR)) { // column 1
		// 	nk_group_end(ctx);
		// }

		// nk_layout_row_push(ctx, 320);
		// if (nk_group_begin(ctx, "column2", NK_WINDOW_NO_SCROLLBAR)) { // column 1
		// 	nk_layout_row_dynamic(ctx, 75, 1);
		// 	if (nk_button_label(ctx, "Back"))
		// 	{
		// 		this->setActive(false);
		// 		mainMenu->setActive(true);
		// 	}

		// 	nk_group_end(ctx);
		// }
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