#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

namespace Gameplay
{
	namespace Collection
	{
		class StickCollectionModel;
		class stickCollectionView;
		enum class SearchType;
		struct Stick;

		class StickCollectionController
		{
		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void update();
			void render();

			void reset();
			void searchElement(SearchType search_type);

			SearchType getSearchType();
			int getNumberOfSticks();
			int getNumberOfComparisions();
			int getNumberOfArrayAccess();
			int getDelayMiliseconds();
			sf::String getTimeComplexity();

		private:
			stickCollectionView* collection_view;
			StickCollectionModel* collection_model;

			std::vector<Stick*> sticks;
			Stick* stick_to_search;

			Collection::SearchType search_type;
			std::thread search_thread;

			int number_of_comparision;
			int number_of_array_access;
			int current_operation_delay;
			int delay_in_ms;
			sf::String time_complexity;

			void initializeSticks();
			float calculateStickWidth();
			float calculateStickHeight(int array_pos);

			void updateSticksPosition();
			void initializeSticksArray();
			void shuffleSticks();

			void resetSticksColor();
			void resetSearchStick();
			void resetVariables();

			void processLinearSearch();
			void processSearchThreadState();
			void joinThreads();

			void destroy();
		};
	}
}