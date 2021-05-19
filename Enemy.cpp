#include "Enemy.h"

Enemy::Enemy(const float spawnX, const float spawnY, const float toX, const bool upDown)
{
	this->coronaSprite.setPosition(sf::Vector2f(spawnX, spawnY));

	this->fromX = spawnX;
	this->fromY = spawnY;
	this->toX = toX;
	this->upDown = upDown;

	velocityX = 1.f;
	if (upDown == true)
	{
		velocityY = -1.f;
	}
}

void Enemy::update(const float& dt)
{

	if (this->coronaSprite.getPosition().x < fromX)
	{
		velocityX = 1.f;

		if (upDown == true)
		{
			velocityY = -1.f;
		}
	}

	if (this->coronaSprite.getPosition().x > toX)
	{
		velocityX = -1.f;

		if (upDown == true)
		{
			velocityY = 1.f;
		}
	}





	this->move(dt, velocityX, velocityY);
}

void Enemy::render(sf::RenderTarget* target)
{
	coronaTexture.loadFromFile("bilder/corona.png", sf::IntRect(0, 0, 50, 50));
	coronaSprite.setTexture(coronaTexture, true);
	target->draw(coronaSprite);
}

sf::Vector2f Enemy::getLocation() const
{
	return sf::Vector2f();
}

void Enemy::move(const float& dt, const float x, const float y)
{
	this->coronaSprite.move(dt * this->speed * x, dt * this->speed * y);
}

bool Enemy::intersects(const sf::FloatRect playBounds)
{
	if (this->coronaSprite.getGlobalBounds().intersects(playBounds)) {
		return true;
	}
	else {
		return false;
	}
}
