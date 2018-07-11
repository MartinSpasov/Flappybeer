#pragma once
#include <SFML\Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace BeerEngine {

	class Flash {
	public:
		Flash(GameDataRef data);
		void Show(float dt);
		void Draw();
	private:
		GameDataRef _data;
		sf::RectangleShape _shape;
		bool _flashOn;
	};

}

