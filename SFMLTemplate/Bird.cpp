#include "Bird.hpp"

namespace BeerEngine {
	Bird::Bird(GameDataRef data) : _data(data){
		_animationIter = 0;
		_frames.push_back(_data->assets.GetTexture("bird1"));
		_frames.push_back(_data->assets.GetTexture("bird2"));
		_frames.push_back(_data->assets.GetTexture("bird3"));
		_frames.push_back(_data->assets.GetTexture("bird4"));

		_sprite.setTexture(_frames.at(0));
		_sprite.setPosition((_data->window.getSize().x / 4) - (_sprite.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_sprite.getGlobalBounds().height / 2));

		sf::Vector2f origin = sf::Vector2f(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
		_sprite.setOrigin(origin);
		_rotation = 0;
		_velocity = 0;
	}

	void Bird::Draw(){
		_data->window.draw(_sprite);
	}

	void Bird::Animate(float dt) {
		if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION / _frames.size()) {
			if (_animationIter < _frames.size() - 1) 
				_animationIter++;
			else
				_animationIter = 0;

			_sprite.setTexture(_frames.at(_animationIter));
			_clock.restart();

		}
	}
	void Bird::Update(float dt){
		if (_velocity > 0) {
			_rotation += ROTATION_SPEED * dt;
			if (_rotation > 80.0f)
				_rotation = 80.0f;
			_sprite.setRotation(_rotation);
		}
		else if (_velocity <= 0) {
			_rotation -= ROTATION_SPEED * 3 * dt;
			if (_rotation < -25.0f)
				_rotation = -25.0f;

			_sprite.setRotation(_rotation);
		}

		_sprite.move(0, _velocity * dt);
		_velocity += GRAVITY * GRAVITY * dt;
	}
	void Bird::Flap(){
		_velocity = -FLYING_SPEED;
	}
	const sf::Sprite & Bird::GetSprite() const{
		return _sprite;
	}
}
