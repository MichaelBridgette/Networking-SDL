#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ServerConnection.h"
#include "Player.h"

class Game 
{
public:
	Game();
	~Game();
	void init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);
	void handleEvents();
	void update();
	void draw();
	void clean();
	bool running();

private:
	bool isRunning;
	SDL_Window * window;
	SDL_Renderer * renderer;

	ServerConnection m_serverConn;

	Player * player1;
	Player * player2;
};

#endif // !GAME_H