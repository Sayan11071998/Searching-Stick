#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

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

			SearchType getSearchType();
			int getNumberOfSticks();

		private:
			stickCollectionView* collection_view;
			StickCollectionModel* collection_model;

			std::vector<Stick*> sticks;

			Collection::SearchType search_type;

			void initializeSticks();
			float calculateStickWidth();

			void updateSticksPosition();
			void resetSticksColor();
			void initializeSticksArray();
			float calculateStickHeight(int array_pos);

			void destroy();
		};
	}
}