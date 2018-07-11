#pragma once

#include <SFML\Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "DEFINITIONS.hpp"

namespace BeerEngine {
	class Pipe{
	public:
		Pipe(GameDataRef data);
		void DrawPipes();
		void SpawnBottomPipe();
		void SpawnTopPipe();
		void SpawnScorePipe();
		void SpawnInvisiblePipe();
		void MovePipes(float dt);
		void RandomizeOffset();

		const std::vector<sf::Sprite> &getSprites() const;
		std::vector<sf::Sprite> &getScoreSprites() ;
	private:
		GameDataRef _data;
		std::vector<sf::Sprite> pipeSprites;
		std::vector<sf::Sprite> scoringPipes;

		int _landHeight;
		int _pipeSpawnYOffset;
	};

}

