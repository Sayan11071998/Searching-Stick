#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include "Gameplay/StickCollection/Stick.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"
#include <iostream>
#include <random>

namespace Gameplay
{
	namespace Collection
	{
		using namespace UI::UIElement;
		using namespace Global;
		using namespace Graphics;

		Gameplay::Collection::StickCollectionController::StickCollectionController()
		{
			collection_view = new StickCollectionView();
			collection_model = new StickCollectionModel();
			initializeSticksArray();
		}

		StickCollectionController::~StickCollectionController() { destroy(); }

		void StickCollectionController::initialize()
		{
			initializeSticks();
			reset();
		}

		void StickCollectionController::update()
		{
			for (int i = 0; i < sticks.size(); i++) { sticks[i]->stick_view->update(); }
		}

		void StickCollectionController::render()
		{
			for (int i = 0; i < sticks.size(); i++) { sticks[i]->stick_view->render(); }
		}

		void Gameplay::Collection::StickCollectionController::reset()
		{
			updateSticksPosition();
			resetSticksColor();
			shuffleSticks();
		}

		void Gameplay::Collection::StickCollectionController::initializeSticks()
		{
			float rectangle_width = calculateStickWidth();

			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				float rectangle_height = calculateStickHeight(i);
				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);
				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, collection_model->element_color);
			}
		}

		float Gameplay::Collection::StickCollectionController::calculateStickWidth()
		{
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);
			float total_spacing = collection_model->space_percentage * total_space;
			float space_between = total_spacing / (collection_model->number_of_elements - 1);
			collection_model->setElementSpacing(space_between);
			float remaining_space = total_space - total_spacing;
			float rectangle_width = remaining_space / collection_model->number_of_elements;

			return rectangle_width;
		}

		float Gameplay::Collection::StickCollectionController::calculateStickHeight(int array_pos)
		{
			return (static_cast<float>(array_pos + 1) / collection_model->number_of_elements) * collection_model->max_element_height;
		}

		void Gameplay::Collection::StickCollectionController::updateSticksPosition()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				float x_position = (i * sticks[i]->stick_view->getSize().x) + ((i + 1) * collection_model->elements_spacing);
				float y_position = collection_model->element_y_position - sticks[i]->stick_view->getSize().y;

				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}

		void Gameplay::Collection::StickCollectionController::initializeSticksArray()
		{
			for (int i = 0; i < collection_model->number_of_elements; i++)
				sticks.push_back(new Stick(i));
		}

		void Gameplay::Collection::StickCollectionController::shuffleSticks()
		{
			std::random_device device;
			std::mt19937 random_engine(device());
			std::shuffle(sticks.begin(), sticks.end(), random_engine);
		}

		void StickCollectionController::resetSticksColor()
		{
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->setFillColor(collection_model->element_color);
		}

		void StickCollectionController::resetVariables()
		{
		}

		void Gameplay::Collection::StickCollectionController::resetSearchStick()
		{
			stick_to_search = sticks[std::rand() % sticks.size()];
			stick_to_search->stick_view->setFillColor(collection_model->search_element_color);
		}

		void Gameplay::Collection::StickCollectionController::processLinearSearch()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				number_of_array_access += 1;
				number_of_comparision++;

				Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::COMPARE_SFX);

				if (sticks[i] == stick_to_search)
				{
					stick_to_search->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;
					return;
				}
				else
				{
					sticks[i]->stick_view->setFillColor(collection_model->processing_element_color);
					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));
					sticks[i]->stick_view->setFillColor(collection_model->element_color);
				}
			}
		}

		void Gameplay::Collection::StickCollectionController::destroy()
		{
			for (int i = 0; i < sticks.size(); i++) { delete sticks[i]; }
			sticks.clear();

			delete collection_view;
			delete collection_model;
		}

		void Gameplay::Collection::StickCollectionController::searchElement(SearchType search_type)
		{

		}

		SearchType Gameplay::Collection::StickCollectionController::getSearchType() { return search_type; }

		int Gameplay::Collection::StickCollectionController::getNumberOfSticks() { return collection_model->number_of_elements; }

		int StickCollectionController::getNumberOfComparisions()
		{
			return 0;
		}

		int StickCollectionController::getNumberOfArrayAccess()
		{
			return 0;
		}
	}
}