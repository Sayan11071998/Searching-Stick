#include "Gameplay/GameplayService.h"
#include "Gameplay/GameplayController.h"
#include "Global/ServiceLocator.h"

namespace Gameplay
{
	using namespace Global;

	GameplayService::GameplayService()
	{
	}

	GameplayService::~GameplayService()
	{
	}

	void GameplayService::initializeRandomSeed()
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
	}

	void GameplayService::initialize()
	{
		initializeRandomSeed();
	}

	void GameplayService::update()
	{
	}

	void GameplayService::render()
	{
	}

	void GameplayService::reset()
	{
	}
}