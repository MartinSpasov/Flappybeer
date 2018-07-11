#include "GameState.hpp"
#include <sstream>
#include "DEFINITIONS.hpp"
#include <iostream>
#include "GameOverState.hpp"
#include "SerialPort.h"


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
		_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPRE_FILEPATH);
		_data->assets.LoadFont("Flappy Font", FLAPPY_FONT);

		pipe = new Pipe(_data);
		land = new Land(_data);
		bird = new Bird(_data);
		flash = new Flash(_data);
		hud = new HUD(_data);

		_score = 0;
		hud->UpdateScore(_score);
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
				_data->arduino.writeSerialPort("ON", MAX_DATA_LENGTH);
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
				
				pipe->RandomizeOffset();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnInvisiblePipe();
				pipe->SpawnScorePipe();
				clock.restart();
			}
			bird->Update(dt);
			std::vector<sf::Sprite> landSprites = land->getSprite();
			for (int i = 0; i < landSprites.size(); i++) {
				if (collision.CheckSpriteCollision(bird->GetSprite(),0.625f, landSprites.at(i), 1.0f)) {
					_gameState = GameStates::eGameover;
					clock.restart();
				}
			}
			std::vector<sf::Sprite> pipeSprites = pipe->getSprites();
			for (int i = 0; i < pipeSprites.size(); i++) {
				if (collision.CheckSpriteCollision(bird->GetSprite(),0.625f, pipeSprites.at(i), 1.0f)) {
					_gameState = GameStates::eGameover;
					clock.restart();
				}
			}
			if (_gameState == GameStates::ePlaying) {
				std::vector<sf::Sprite> &scoreSprites = pipe->getScoreSprites();
				for (int i = 0; i < scoreSprites.size(); i++) {
					if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoreSprites.at(i), 1.0f)) {
						_score++;
						hud->UpdateScore(_score);
						scoreSprites.erase(scoreSprites.begin() + i);
					}
				}
			}
		}
		if (_gameState == GameStates::eGameover) {
			flash->Show(dt);
			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GO) {
				this->_data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
			}
		}

	
	}

	void GameState::Draw(float dt) {
		_data->window.clear();
		_data->window.draw(_background);
		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();
		flash->Draw();
		hud->Draw();
		_data->window.display();
		
	}

}


