#pragma once

#include <SFML\Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace BeerEngine {
	class Land
	{
	public:
		Land(GameDataRef data);
		void MoveLand(float dt);
		void DrawLand();
		const std::vector<sf::Sprite> &getSprite() const;

	private:
		GameDataRef _data;
		std::vector<sf::Sprite> _landSprites;
	};
}


