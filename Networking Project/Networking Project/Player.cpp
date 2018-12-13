#include "Player.h"

Player::Player(const char * name, int width, int height, SDL_Renderer * renderer, float x, float y)
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
	if (left && inBoundaries())
	{
		posX -= 0.1;
	}
	if (right && inBoundaries())
	{
		posX += 0.1;
	}
	if (up && inBoundaries())
	{
		posY -= 0.1;
	}
	if (down && inBoundaries())
	{
		posY += 0.1;
	}
}

void Player::draw()
{
	dstrect = { int(this->posX), int(this->posY), this->width, this->height };
	SDL_RenderCopy(m_renderer, texture, &srcrect, &dstrect);
}

void Player::handleInput(SDL_Keycode key)
{
	if (hasControl)
	{
		switch (key)
		{
		case SDLK_a:
			left = true;
			break;
		case SDLK_d:
			right = true;
			break;
		case SDLK_w:
			up = true;
			break;
		case SDLK_s:
			down = true;
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

bool Player::inBoundaries()
{
	if (posX  > 1200 - (radius*2))
	{
		posX = 1200 - (radius*2);
		return false;
	}

	if (posX  < 0)
	{
		posX = 0;
		return false;
	}

	if (posY  > 900 -(radius * 2))
	{
		posY = 900- (radius * 2);
		return false;
	}

	if (posY  < 0)
	{
		posY = 0;
		return false;
	}

	return true;
}
