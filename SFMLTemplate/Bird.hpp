#pragma once
#include <SFML\Graphics.hpp>
#include "DEFINITIONS.hpp"
#include  "Game.hpp"
#include <vector>
namespace BeerEngine {
	class Bird{
	public:
		Bird(GameDataRef data);
		void Draw();
		void Animate(float dt);
		void Update(float dt);
		void Flap();
		const sf::Sprite &GetSprite() const;
	private:
		GameDataRef _data;
		sf::Sprite _sprite;
		std::vector<sf::Texture> _frames;
		unsigned int _animationIter;
		sf::Clock _clock;
		float _rotation;
		int _velocity;
	};

}


