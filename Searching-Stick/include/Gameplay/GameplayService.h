#pragma once
#include <SFML/System/String.hpp>

namespace Gameplay
{
	class GameplayController;

	class GameplayService
	{
	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void reset();

	private:
		GameplayController* gameplay_controller;
	};
}