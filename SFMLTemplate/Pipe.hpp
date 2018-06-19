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
		void SpawnInvisiblePipe();
		void MovePipes(float dt);
		void RandomizeOffset();

		const std::vector<sf::Sprite> &getSprites() const;
	private:
		GameDataRef _data;
		std::vector<sf::Sprite> pipeSprites;

		int _landHeight;
		int _pipeSpawnYOffset;
	};

}

