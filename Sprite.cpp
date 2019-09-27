#include "Sprite.h"
#include "Error.h"

bool Sprite::Load(std::string path)
{
	if (texture)
		Unload();

	// Load image into surface
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		std::string message = "Unable to load image ";
		message.append(path);
		message.append("\nSDL_image error: ");
		message.append(IMG_GetError());
		Error(message, false);
		return false;
	}
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = surface->w;
	srcRect.h = surface->h;
	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = surface->w;
	dstRect.h = surface->h;
	//width = surface->w;
	//height = surface->h;

	// Create a texture from surface
	texture = SDL_CreateTextureFromSurface(&renderer, surface);
	if (texture == nullptr)
	{
		Error("Unable to create texture from " + path);
		return false;
	}
	SDL_FreeSurface(surface);

	return true;
}

void Sprite::Unload()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Sprite::SetRects(SDL_Rect srcRect, SDL_Rect dstRect)
{
	this->srcRect = srcRect;
	this->dstRect = dstRect;
}

int Sprite::GetWidth()
{
	if (texture == nullptr)
		return 0;
	return srcRect.w - srcRect.x;
}

int Sprite::GetHeight()
{
	if (texture == nullptr)
		return 0;
	return srcRect.h - srcRect.y;
}

void Sprite::SetPosition(int x, int y)
{
	dstRect.x = x;
	dstRect.y = y;
}
