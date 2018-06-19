#include "GameState.hpp"
#include <sstream>
#include "DEFINITIONS.hpp"
#include <iostream>


namespace BeerEngine {
	GameState::GameState(GameDataRef data) : _data(data) {}

	void GameState::Init() {
		_data->assets.LoadTexture("Game Background", GAME_BACKGROUNF_FILEPATH);
		_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		_data->assets.LoadTexture("Land", LAND_FILEPATH);
		_data->assets.LoadTexture("bird1", BIRD_FRAME_1_FILEPATH);
		_data->assets.LoadTexture("bird2", BIRD_FRAME_2_FILEPATH);
		_data->assets.LoadTexture("bird3", BIRD_FRAME_3_FILEPATH);
		_data->assets.LoadTexture("bird4", BIRD_FRAME_4_FILEPATH);

		pipe = new Pipe(_data);
		land = new Land(_data);
		bird = new Bird(_data);

		_gameState = GameStates::eReady;

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

	}

	void GameState::HandleInput() {
		sf::Event event;

		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type)
				_data->window.close();
		}

		if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window)) {
			if (_gameState != GameStates::eGameover) {
				_gameState = GameStates::ePlaying;
				bird->Flap();
			}
		}
	}

	void GameState::Update(float dt) {
		if (_gameState != GameStates::eGameover) {
			bird->Animate(dt);
			land->MoveLand(dt);
		}
		if (_gameState == GameStates::ePlaying) {
			pipe->MovePipes(dt);

			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_RATE) {
				//pipe->SpawnInvisiblePipe();
				pipe->RandomizeOffset();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();

				clock.restart();
			}
			bird->Update(dt);
			std::vector<sf::Sprite> landSprites = land->getSprite();
			for (int i = 0; i < landSprites.size(); i++) {
				if (collision.CheckSpriteCollision(bird->GetSprite(),0.625f, landSprites.at(i), 1.0f)) {
					_gameState = GameStates::eGameover;
				}
			}
			std::vector<sf::Sprite> pipeSprites = pipe->getSprites();
			for (int i = 0; i < pipeSprites.size(); i++) {
				if (collision.CheckSpriteCollision(bird->GetSprite(),0.625f, pipeSprites.at(i), 1.0f)) {
					_gameState = GameStates::eGameover;
				}
			}
		}
		
	
	}

	void GameState::Draw(float dt) {
		_data->window.clear();
		_data->window.draw(_background);
		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();
		_data->window.display();
	}

}


