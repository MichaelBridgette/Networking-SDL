#include "Player.h"

Player::Player(const char * name, int width, int height, SDL_Renderer * renderer, int x, int y)
{
	this->width = width;
	this->height = height;
	srcrect = { 0, 0, this->width, this->height };
	dstrect = { 0, 0, this->width, this->height };
	m_renderer = renderer;
	image = IMG_Load(name);
	texture = SDL_CreateTextureFromSurface(m_renderer, image);
	posX = x;
	posY = y;

	if (!texture)
	{
		std::cout << name << " texture failed to load!" << std::endl;
	}
	radius = 32;
}

void Player::update()
{
}

void Player::draw()
{
	dstrect = { this->posX, this->posY, this->width, this->height };
	SDL_RenderCopy(m_renderer, texture, &srcrect, &dstrect);
}

void Player::handleInput(SDL_Keycode key)
{
	if (hasControl)
	{
		switch (key)
		{
		case SDLK_a:
			posX += -5;
			break;
		case SDLK_d:
			posX += 5;
			break;
		case SDLK_w:
			posY += -5;
			break;
		case SDLK_s:
			posY += 5;
			break;
		default:
			break;
		}
	}
}

void Player::giveControl(bool c)
{
	hasControl = c;
}

bool Player::collisionDetection(int x, int y, int r)
{
	int a = radius + r;
	int xDist = posX - x;
	int yDist = posY - y;
	return a > sqrt((xDist * xDist) + (yDist * yDist));
}
