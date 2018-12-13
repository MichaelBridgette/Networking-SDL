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
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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



	font = TTF_OpenFont("arial.ttf", 100); //this opens a font style and sets a size
	if (font == NULL)
	{
		std::cout << "font not found" << std::endl;
	}
	SDL_Color color = { 255, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	surfaceMessage = TTF_RenderText_Solid(font, "Game Over!", color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	//SDL_FreeSurface(surfaceMessage);
	Message_rect.x = 400;  //controls the rect's x coordinate 
	Message_rect.y = 250; // controls the rect's y coordinte
	Message_rect.w = 400; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
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
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			player2->left = false;
			break;
		case SDLK_d:
			player2->right = false;
			break;
		case SDLK_w:
			player2->up = false;
			break;
		case SDLK_s:
			player2->down = false;
			break;
		default:
			break;
		}
		break;
	}

}

void Game::update()
{
	std::string received = "";
	switch (state)
	{
	case GameState::PLAY:
		player2->update();
		if (player1->collisionDetection(player2->posX, player2->posY, player2->radius))
		{
			//std::cout << "Collision Detected!!!" << std::endl;
			state = GameState::GAMEOVER;
		}
		m_serverConn.sendMessage(std::to_string(player2->posX) + "," + std::to_string(player2->posY));
		received = m_serverConn.receiveMessage();
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
		break;
	case GameState::GAMEOVER:

		break;
	default:
		break;
	}
	
}

void Game::draw()
{
	SDL_RenderClear(renderer);
	//this is where we draw stuff

	switch (state)
	{
	case GameState::PLAY:
		//SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
		player1->draw();
		player2->draw();
		break;
	case GameState::GAMEOVER:
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
		break;
	}
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
