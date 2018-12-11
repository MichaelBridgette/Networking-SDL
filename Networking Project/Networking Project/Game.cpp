#include "Game.h"
#include<iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char * title, int xPos, int yPos, int width, int height, bool fullScreen)
{
	int flags = 0;

	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{


		std::cout << "Subsystems initialised!" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
			std::cout << "Renderer created!" << std::endl;


		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
	if (!IMG_Init(IMG_INIT_PNG) == 0)
	{

	}
	else
	{
		std::cout << IMG_GetError() << std::endl;
	}


	player1 = new Player("circle.png", 64, 64, renderer, 100, 100);
	//player1->giveControl(true);
	player2 = new Player("circle2.png", 64, 64, renderer, 500, 500);
	player2->giveControl(true);
}

void Game::HandleEvents()
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

void Game::Update()
{
	if (player1->collisionDetection(player2->posX, player2->posY, player2->radius))
	{
		std::cout << "Collision Detected!!!" << std::endl;
	}
}

void Game::Draw()
{
	SDL_RenderClear(renderer);
	//this is where we draw stuff
	player1->draw();
	player2->draw();
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}

bool Game::Running()
{
	return isRunning;
}
