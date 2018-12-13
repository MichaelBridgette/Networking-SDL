#include "Game.h"

Game::Game() {}

Game::~Game() {}

void Game::init(const char * title, int xPos, int yPos, int width, int height, bool fullScreen)
{
	int flags = 0;

	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialised" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}
	if (!IMG_Init(IMG_INIT_PNG) == 0)
	{
		// TBI...
	}
	else
	{
		std::cout << IMG_GetError() << std::endl;
	}

	if (!m_serverConn.initialise())
	{
		std::cout << "An error occured while connecting to the server" << std::endl;
	}
	else
	{
		std::cout << "Server connection made" << std::endl;
	}

	player1 = new Player("circle.png", 64, 64, renderer, 100, 100);
	//player1->giveControl(true);
	player2 = new Player("circle2.png", 64, 64, renderer, 500, 500);
	player2->giveControl(true);
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;

	case SDL_KEYDOWN:
		player1->handleInput(event.key.keysym.sym);
		player2->handleInput(event.key.keysym.sym);
		break;
	}

}

void Game::update()
{
	if (player1->collisionDetection(player2->posX, player2->posY, player2->radius))
	{
		std::cout << "Collision Detected!!!" << std::endl;
	}
	m_serverConn.sendMessage(std::to_string(player2->posX) + "," + std::to_string(player2->posY));
	std::string received = m_serverConn.receiveMessage();
	if ("" != received)
	{
		if ("1" == received)
		{
			player2->posX = 100;
			player2->posY = 100;
		}
		else if ("2" == received)
		{
			player2->posX = 500;
			player2->posY = 500;
		}
		else
		{
			std::string delimeter = ",";
			std::string otherX = received.substr(0, received.find(delimeter));
			std::string otherY = received.substr(received.find(delimeter) + 1, received.length());
			player1->posX = std::stoi(otherX);
			player1->posY = std::stoi(otherY);
		}
	}
}

void Game::draw()
{
	SDL_RenderClear(renderer);
	//this is where we draw stuff
	player1->draw();
	player2->draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}

bool Game::running()
{
	return isRunning;
}
