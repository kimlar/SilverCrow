#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Sprite
{
public:
	Sprite(SDL_Renderer& renderer) : renderer(renderer) {}
	virtual ~Sprite() {}

	bool Load(std::string path);
	void Unload();

	void SetRects(SDL_Rect srcRect, SDL_Rect dstRect);
	SDL_Rect GetSrcRect() { return srcRect; }
	SDL_Rect GetDstRect() { return dstRect; }

	SDL_Texture& GetTexture() { return *texture; }

	int GetWidth();
	int GetHeight();

	void SetPosition(int x, int y);

private:
	SDL_Renderer& renderer;
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
};
