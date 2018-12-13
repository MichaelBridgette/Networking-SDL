#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ServerConnection.h"
#include "Player.h"
#include <SDL_ttf.h>

enum GameState {
	PLAY,
	GAMEOVER
};

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

	float startX = 0;
	float startY = 0;
	float startX2 = 0;
	float startY2 = 0;

	SDL_Window * window;
	SDL_Renderer * renderer;

	ServerConnection m_serverConn;

	Player * player1;
	Player * player2;

	GameState state = GameState::PLAY;
	TTF_Font* font;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;
	SDL_Rect Message_rect;
};

#endif // !GAME_H