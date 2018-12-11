#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"Player.h"
class Game {
public:
	Game();
	~Game();
	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);

	void HandleEvents();
	void Update();
	void Draw();
	void Clean();

	bool Running();

private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
	Player * player1;

	Player * player2;
};
