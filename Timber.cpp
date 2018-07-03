// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

// Make code easier to type with "using namespace"
using namespace sf;

void updateBranches(int);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side {LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];

int main()
{
	auto screenWidth = 1920, screenHeight = 1080;
	// Create a video mode object
	VideoMode vm(screenWidth, screenHeight);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", sf::Style::Resize);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	bool beeActive = false;
	float beeSpeed = 0.0f;

	// make 3 cloud sprites from 1 texture
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	// Position the clouds off screen
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 150);
	spriteCloud3.setPosition(0, 300);

	// Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// pause feature
	bool paused = true;

	//Draw text
	int score = 0;
	Text messageText;
	Text scoreText;

	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	messageText.setFont(font);
	scoreText.setFont(font);

	//assign actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	messageText.setColor(Color::White);
	scoreText.setColor(Color::White);

	//Place text
	scoreText.setPosition(20, 20);

	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	messageText.setPosition(screenWidth / 2.0f, screenHeight / 2.0f);

	// Variables to control time itself
	Clock clock;


	//time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((screenWidth / 2) - timeBarStartWidth/2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


	//Prepare 6 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	
	for(int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	while (window.isOpen())
	{

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			//Reset timer
			score = 0;
			timeRemaining = 5;
		}

		if (!paused)
		{

			//Measure TIme
			Time dt = clock.restart();

			timeRemaining -= dt.asSeconds();
			timeBar.setSize(Vector2f( timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				paused = true;

				messageText.setString("You're out of time");

				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				messageText.setPosition(screenWidth / 2.0f, screenHeight / 2.0f);
			}

			if (!beeActive)
			{

				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			{
				spriteBee.setPosition(
					spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				if (spriteBee.getPosition().x < -100)
				{
					beeActive = false;
				}
			}

			// Cloud 1
			if (!cloud1Active)
			{
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else
			{

				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);

				if (spriteCloud1.getPosition().x > 1920)
				{
					cloud1Active = false;
				}
			}
			// Cloud 2
			if (!cloud2Active)
			{

				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
			{

				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);

				if (spriteCloud2.getPosition().x > 1920)
				{
					cloud2Active = false;
				}
			}

			if (!cloud3Active)
			{
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);

				if (spriteCloud3.getPosition().x > 1920)
				{
					cloud3Active = false;
				}
			}

			//update score
			std::stringstream ss;
			ss << "Score : " << score;
			scoreText.setString(ss.str());

			
			for(size_t i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i*150;

				if(branchPositions[i] == side::LEFT){ // when is this assigned??
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if(branchPositions[i] == side::RIGHT){
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else{
					branches[i].setPosition(3000, height);
				}
			}
			

		}
		// Clear everything from the last frame
		window.clear();

		// Draw scene
		window.draw(spriteBackground);

		// Draw clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		//draw branches
		for(int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}
		

		window.draw(spriteTree);
		window.draw(spriteBee);
		window.draw(scoreText);
		window.draw(timeBar);
		if (paused) {
			window.draw(messageText);
		}
		window.display();
	}

	return 0;
}

void updateBranches(int seed){
	
	for(int j = NUM_BRANCHES -1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j-1];
	}
	
	srand((int)time(0) + seed);
	int r = (rand()%5);
	switch(r){
		case 0:
			branchPositions[0] = side::LEFT;
			break;

		case 1:
			branchPositions[0] = side::RIGHT;
			break;

		default:
			branchPositions[0] = side::NONE;
			break;
	}
}