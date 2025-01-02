#pragma once

namespace Gameplay
{
	class GameplayView;

	class GameplayController
	{
	public:
		GameplayController();
		~GameplayController();

		void initialize();
		void update();
		void render();

		void reset();

	private:
		GameplayView* gameplay_view;

		void destroy();
	};
}