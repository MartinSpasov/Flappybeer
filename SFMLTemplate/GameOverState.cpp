#include "GameOverState.hpp"
#include <sstream>
#include "DEFINITIONS.hpp"
#include <iostream>
#include "GameState.hpp"
#include <fstream>

namespace BeerEngine {
	GameOverState::GameOverState(GameDataRef data, int score) : _data(data), _score(score) {

	}

	void GameOverState::Init() {
		std::ifstream readFile;
		readFile.open(HIGHSCORE_FILEPATH);
		if (readFile.is_open()) {
			while (!readFile.eof()) {
				readFile >> _highscore;
			}
		}
		readFile.close();

		if (_score > _highscore) {
			_highscore = _score;
			std::ofstream writeFile(HIGHSCORE_FILEPATH);
			if (writeFile.is_open()) {
				writeFile << _highscore;
			}
			writeFile.close();
		}
		
		_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Game Over Title", GAME_OVER_FILEPATH);
		_data->assets.LoadTexture("Game Over Body", GAME_OVER__BODY_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
		_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
		_gameOverContainer.setTexture(this->_data->assets.GetTexture("Game Over Body"));
		_retryButton.setTexture(this->_data->assets.GetTexture("Play Button"));

		_gameOverContainer.setPosition(_data->window.getSize().x / 2 - _gameOverContainer.getGlobalBounds().width / 2, _data->window.getSize().y * (1.0 / 3.0));
		_gameOverTitle.setPosition(_data->window.getSize().x / 2 - _gameOverTitle.getGlobalBounds().width/2 , _data->window.getSize().y / 8 -_gameOverTitle.getGlobalBounds().height / 2);
		_retryButton.setPosition(_data->window.getSize().x / 2 - _retryButton.getGlobalBounds().width / 2, _data->window.getSize().y * (2.0 / 3.0 ));

		_scoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_scoreText.setString(std::to_string(_score));
		_scoreText.setCharacterSize(56);
		_scoreText.setFillColor(sf::Color::White);
		_scoreText.setOrigin(_scoreText.getGlobalBounds().width/2 , _scoreText.getGlobalBounds().height / 2);
		_scoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 2.15 - 34);

		_highscoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_highscoreText.setString(std::to_string(_highscore));
		_highscoreText.setCharacterSize(56);
		_highscoreText.setFillColor(sf::Color::White);
		_highscoreText.setOrigin(_highscoreText.getGlobalBounds().width / 2, _highscoreText.getGlobalBounds().height / 2 );
		_highscoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 1.78 - 34);
	}

	void GameOverState::HandleInput() {
		sf::Event event;

		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type)
				_data->window.close();
			if (_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window)) {
				_data->machine.AddState(StateRef(new GameState(_data)));
			}
		}
	}
	void GameOverState::Update(float dt) {
	
	}

	void GameOverState::Draw(float dt) {
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_gameOverContainer);
		_data->window.draw(_gameOverTitle);
		_data->window.draw(_retryButton);
		_data->window.draw(_highscoreText);
		_data->window.draw(_scoreText);
		_data->window.display();
	}

}


