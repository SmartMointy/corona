#pragma once
#include "Player.h"
#define ROUNDF(f, c) (((float)((int)((f) * (c))) / (c)))

class Engine
{
private:
	Player player;
	sf::Clock dtClock;
	sf::Clock timeClock;
	float dt;
	float record = 0;
	sf::Font font;
	sf::Text goal;
	std::vector<sf::Sprite> walls;
	std::vector<Enemy> enemies;
	std::vector<sf::Sprite> coins;
	sf::Text coinCountText;
	sf::RectangleShape coinCountBackground;

	sf::RenderWindow* window;
	sf::Event event;

	bool gameOver = false;
	bool won = false;
	bool lost = false;
	int coinCount = 0;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	float getTime();

	// Private methods
	void createWindow();
	void createWalls();
	void createEnemies();
	void createCoins();
public:
	// Constuctor / Deconstructor
	Engine();
	virtual ~Engine();

	// Methods
	const bool getWindowIsOpen() const;

	void updateDt();
	void updateEvents();
	void update();
	void render();

	void startTimer();
	void reset();

};

