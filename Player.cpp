#include "Player.h"

Player::Player(const float& x, const float& y)
{
	if (!playerTexture.loadFromFile("bilder/player.png", sf::IntRect(0, 0, 50, 50)))
	{
		// error...
	}
	playerSprite.setTexture(playerTexture, true);
	playerSprite.setOrigin(25.f, 25.f);
	playerSprite.setPosition(x, y);

	this->velocityX = 0.f;
	this->velocityY = 0.f;

}

void Player::update(const float& dt, std::vector<sf::Sprite> walls)
{
	velocityX = 0.f;
	velocityY = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocityX = -1.f;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocityX = 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocityY = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocityY = 1.f;
	}

	// Collision
	if (this->getLocation().x - 25.f < 0)
	{
		this->playerSprite.setPosition(25.f, this->getLocation().y);
	}
	if (this->getLocation().x + 25.f > 1200) {
		this->playerSprite.setPosition(1200 - 25.f, this->getLocation().y);
	}
	if (this->getLocation().y - 25.f < 0) {
		this->playerSprite.setPosition(this->getLocation().x, 25.f);
	}
	if (this->getLocation().y + 25.f > 700) {
		this->playerSprite.setPosition(this->getLocation().x, 700 - 25.f);
	}



	sf::FloatRect playerBounds = this->playerSprite.getGlobalBounds();

	for (auto& wall : walls)
	{
		sf::FloatRect wallBounds = wall.getGlobalBounds();
		sf::FloatRect playerBounds = this->playerSprite.getGlobalBounds();

		this->nextPos = playerBounds;
		this->nextPos.left += dt * this->speed * velocityX;
		this->nextPos.top += dt * this->speed * velocityY;

		if (wallBounds.intersects(nextPos))
		{
			// Bottom Collision
			if (playerBounds.top < wallBounds.top
				&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left)
			{
				velocityY = 0.f;
				playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, wallBounds.top - (playerBounds.height / 2)));
			}

			// Top Collision
			else if (playerBounds.top > wallBounds.top
				&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left)
			{
				velocityY = 0.f;
				playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, wallBounds.top + wallBounds.height + 25.f));
			}
			// Right Collision
			else if (playerBounds.left < wallBounds.left
				&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top)
			{
				velocityX = 0.f;
				playerSprite.setPosition(sf::Vector2f(wallBounds.left - (playerBounds.width / 2), playerSprite.getPosition().y));
			}

			// Left Collision
			else if (playerBounds.left > wallBounds.left
				&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top)
			{
				velocityX = 0.f;
				playerSprite.setPosition(sf::Vector2f(wallBounds.left + wallBounds.width + 25.f, playerSprite.getPosition().y));
			}


		}

	}
	
	move(dt, velocityX, velocityY);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(playerSprite);
}

sf::Vector2f Player::getLocation() const
{
	return this->playerSprite.getPosition();
}

sf::FloatRect Player::getNextPosition()
{
	return this->nextPos;
}

void Player::setPostition(const sf::Vector2f& pos)
{
	this->playerSprite.setPosition(pos);
}

void Player::move(const float& dt, const float x, const float y)
{
	this->playerSprite.move(dt * this->speed * x, dt * this->speed * y);
}

sf::FloatRect Player::getBounds()
{
	return this->playerSprite.getGlobalBounds();
}
