#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Player {

public:
	// Public Methods
	Player(const char * name, int width, int height, SDL_Renderer * renderer, float x, float y);
	void update();
	void draw();
	void handleInput(SDL_Keycode key);
	void giveControl(bool c);
	bool collisionDetection(int x, int y, int r);
	bool inBoundaries();
	// Public Members
	float posX;
	float posY;
	int radius;

	bool up;
	bool down;
	bool left;
	bool right;
	bool active;
private:
	// Private Members
	SDL_Renderer * m_renderer;
	SDL_Surface * image;
	SDL_Texture * texture;
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	int width;
	int height;

	bool hasControl;
	Uint8* keys;

	

};

#endif // !PLAYER_H
