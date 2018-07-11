#pragma once
#include <SFML\Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"


namespace BeerEngine {
	class GameState : public State {
	public:
		GameState(GameDataRef data);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;

		Pipe *pipe;
		Land *land;
		Bird *bird;
		Collision collision;
		Flash *flash;
		HUD *hud;

		int _gameState;
		sf::Clock clock;
		int _score;

	};
}



