#include "Engine.h"

float Engine::getTime()
{
	return this->timeClock.getElapsedTime().asSeconds();
}

void Engine::createWindow()
{
	sf::VideoMode video_mode(1200, 700);

	this->window = new sf::RenderWindow(video_mode, "Corona", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Engine::createWalls()
{
	sf::Sprite wall;
	wall.setOrigin(250.f, 100.f);
	wall.setPosition(600.f, 350.f);
	walls.push_back(wall);
}

void Engine::createEnemies()
{
	Enemy enemy(30.f, 60.f, 170.f, false);
	enemies.push_back(enemy);

	Enemy enemy2(100.f, 620.f, 300.f, false);
	enemies.push_back(enemy2);

	Enemy enemy3(460.f, 160.f, 600.f, true);
	enemies.push_back(enemy3);

	Enemy enemy4(590.f, 600.f, 740.f, true);
	enemies.push_back(enemy4);

	Enemy enemy5(1000.f, 620.f, 1140.f, true);
	enemies.push_back(enemy5);

	Enemy enemy6(850.f, 325.f, 1150.f, false);
	enemies.push_back(enemy6);
}

void Engine::createCoins()
{
	sf::Sprite coinSprite;

	coinSprite.setPosition(sf::Vector2f(50.f, 50.f));
	coins.push_back(coinSprite);

	coinSprite.setPosition(sf::Vector2f(170.f, 630.f));
	coins.push_back(coinSprite);

	coinSprite.setPosition(sf::Vector2f(460.f, 180.f));
	coins.push_back(coinSprite);

	coinSprite.setPosition(sf::Vector2f(740.f, 440.f));
	coins.push_back(coinSprite);

	coinSprite.setPosition(sf::Vector2f(1000.f, 140.f));
	coins.push_back(coinSprite);

	coinSprite.setPosition(sf::Vector2f(1100.f, 540.f));
	coins.push_back(coinSprite);
}

Engine::Engine()
	: player(25.f, 350.f)
{
	this->createWindow();

	if (backgroundTexture.loadFromFile("bilder/background.png", sf::IntRect(0, 0, 1200, 700)))
	{
		background.setTexture(backgroundTexture, true);
		background.setPosition(sf::Vector2f(0.f, 0.f));
	}

	font.loadFromFile("fonts/arial.ttf");

	goal.setFillColor(sf::Color::Red);
	goal.setCharacterSize(20);
	goal.setString("Ziel");

	goal.setFont(font);

	sf::FloatRect textRect = goal.getLocalBounds();
	goal.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	goal.setPosition(sf::Vector2f(1200 - textRect.width, 700 / 2.0f));

	coinCountText.setFillColor(sf::Color::White);
	coinCountText.setCharacterSize(20);

	coinCountText.setFont(font);
	coinCountText.setPosition(sf::Vector2f(5.f, 5.f));

	coinCountBackground.setSize(sf::Vector2f(110.f, 35.f));
	coinCountBackground.setPosition(sf::Vector2f(0, 0));
	sf::Color col(0, 0, 0, 150);
	coinCountBackground.setFillColor(col);

	this->createWalls();

	this->startTimer();

	this->createEnemies();

	this->createCoins();

}

Engine::~Engine()
{
	delete this->window;
}

// Methods

const bool Engine::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Engine::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Engine::updateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}

}

void Engine::update()
{
	this->updateEvents();

	if (!this->gameOver)
	{
		this->player.update(this->dt, this->walls);

		sf::Vector2f playerLocation = this->player.getLocation();
		if (playerLocation.x >= 1170.f && playerLocation.y >= 340.f && playerLocation.y <= 360.f && this->coinCount >= 6)
		{
			this->gameOver = true;
			this->won = true;
		}

		sf::FloatRect playerBoundsE = player.getBounds();
		playerBoundsE.left = playerBoundsE.left + 6.f;
		playerBoundsE.top = playerBoundsE.top + 6.f;

		playerBoundsE.width = playerBoundsE.width - 12.f;
		playerBoundsE.height = playerBoundsE.height - 12.f;

		for (auto &enemy: enemies)
		{
			enemy.update(dt);
			if (enemy.intersects(playerBoundsE))
			{
				this->gameOver = true;
				this->won = false;
			}
		}

		sf::FloatRect playerBounds = player.getBounds();
		playerBounds.left = playerBounds.left + 25.f;
		playerBounds.top = playerBounds.top + 25.f;
		
		playerBounds.width = playerBounds.width - 45.f;
		playerBounds.height = playerBounds.height - 45.f;

		for (auto& coin : coins)
		{

			if (coin.getGlobalBounds().intersects(playerBounds))
			{
				this->coinCount++;
				coin.setPosition(sf::Vector2f(-50.f, -50.f));
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->reset();
	}
}

void Engine::render()
{
	this->window->clear(sf::Color(161,207,247,255));

	this->window->draw(background);

	if (this->coinCount >= 6)
	{
		this->window->draw(goal);
	}

	sf::Texture wallTexture;

	if (!wallTexture.loadFromFile("bilder/wall.png", sf::IntRect(0, 0, 500, 200)))
	{

	}

	for (auto& wall : walls)
	{
		wall.setTexture(wallTexture, true);
		this->window->draw(wall);
	}

	sf::Texture coinTexture;
	coinTexture.loadFromFile("bilder/coin.png", sf::IntRect(0, 0, 50, 50));

	for (auto& coin : coins)
	{
		coin.setTexture(coinTexture, true);
		this->window->draw(coin);
	}

	for (auto& enemy : enemies)
	{
		enemy.render(this->window);
	}

	sf::Text timerText;
	timerText.setFont(font);

	float x = ROUNDF(getTime(), 100);
	std::string string = std::to_string(x);
	timerText.setString(string.substr(0, string.length() - 4));
	timerText.setPosition(sf::Vector2f((1200 / 2.0f) - 50.f, 0.f));

	sf::RectangleShape bgTimer;
	bgTimer.setSize(sf::Vector2f(120.f, 40.f));
	bgTimer.setPosition(sf::Vector2f((1200 / 2.0f) - 60.f, 0.f));
	sf::Color col(0, 0, 0, 170);
	bgTimer.setFillColor(col);

	this->window->draw(bgTimer);



	if (this->gameOver)
	{
		if (!lost) {
			this->record = this->timeClock.getElapsedTime().asSeconds();
			this->lost = true;
		}
		float x = ROUNDF(this->record, 100);
		std::string string = std::to_string(x);
		timerText.setString(string.substr(0, string.length() - 4));

		sf::Text text;
		text.setFillColor(sf::Color::White);
		if (this->won)
		{
			text.setString("Du hast gewonnen!");
		}
		else {
			text.setString("Du hast verloren!");
		}
		text.setCharacterSize(60);

		text.setFont(font);

		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		text.setPosition(sf::Vector2f(1200 / 2.0f, 700 / 2.0f));

		sf::RectangleShape bg;
		bg.setSize(sf::Vector2f(textRect.width + 100.f, textRect.height + 150.f));
		bg.setPosition(sf::Vector2f((1200 / 2.0f) - ((textRect.width + 100.f) / 2.f), (700 / 2.0f) - ((textRect.height + 150.f) / 2.f)));
		sf::Color col(0, 0, 0, 220);
		bg.setFillColor(col);

		this->window->draw(bg);
		this->window->draw(text);
	}
	
	this->window->draw(timerText);

	coinCountText.setString("Coins: " + std::to_string(coinCount) + " / 6");
	this->window->draw(coinCountBackground);
	this->window->draw(coinCountText);

	this->player.render(window);

	this->window->display();
}

void Engine::startTimer()
{
	this->timeClock.restart().asSeconds();
}

void Engine::reset()
{
	if (getTime() >= 0.3f) {
		gameOver = false;
		won = false;
		lost = false;
		coinCount = 0;
		record = 0;

		player.setPostition(sf::Vector2f(25.f, 350.f));

		for (auto& i : enemies)
		{
			enemies.pop_back();
		}

		enemies.clear();
		coins.clear();

		this->startTimer();

		this->createEnemies();

		this->createCoins();
	}

}
