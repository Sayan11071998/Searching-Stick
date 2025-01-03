#pragma once
#include <SFML/Graphics.hpp>
#include "UI//UIElement/ImageView.h"

namespace Gameplay
{
	class GameplayController;

	class GameplayView
	{
	public:
		GameplayView();
		~GameplayView();

		void initialize(GameplayController* gameplay_controller);
		void update();
		void render();

	private:
		const float background_alpha = 55.f;

		GameplayController* gameplay_controller;
		UI::UIElement::ImageView* background_image;

		sf::Font font;

		void initializeBackgroundImage();
	};
}