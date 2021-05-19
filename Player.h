#pragma once
#include "Enemy.h"

class Player
{
private:
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	const float speed = 100.f;
	sf::FloatRect nextPos;
	float velocityX;
	float velocityY;
public:
	Player(const float& x, const float& y);
	void update(const float& dt, std::vector<sf::Sprite> walls);
	void render(sf::RenderTarget* target);

	sf::Vector2f getLocation() const;

	sf::FloatRect getNextPosition();

	void setPostition(const sf::Vector2f& pos);

	sf::FloatRect getBounds();

	void move(const float& dt, const float x, const float y);
};

