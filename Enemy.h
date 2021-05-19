#pragma once
#include "Coin.h"

class Enemy
{
	const float speed = 160.f;
	sf::Texture coronaTexture;
	sf::Sprite coronaSprite;
	float velocityX = 0.f;
	float velocityY = 0.f;
	float fromX;
	float fromY;
	float toX;
	bool upDown;

public:
	Enemy(const float spawnX, const float spawnY, const float toX, const bool upDown);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	sf::Vector2f getLocation() const;

	void move(const float& dt, const float x, const float y);

	bool intersects(const sf::FloatRect playBounds);
};

