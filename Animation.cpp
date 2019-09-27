#include <SDL_image.h>
#include <fstream>
#include "Animation.h"
#include "Error.h"

Animation::Animation(SDL_Renderer& renderer) : renderer(renderer)
{

}

Animation::~Animation()
{

}

void Animation::Update(float dt)
{
	if (!play)
		return;

	remainingFrameTime -= dt * (float)playSpeed;
	if (remainingFrameTime <= 0.0f)
	{
		if (backwards)
		{
			currentFrame--;
			if (currentFrame < 0)
			{
				if (!loop)
				{
					play = false;
					currentFrame = 0;
				}
				else
					currentFrame = numberOfFrames - 1;
			}
		}
		else
		{
			currentFrame++;
			if (currentFrame >= numberOfFrames)
			{
				if (!loop)
				{
					play = false;
					currentFrame = numberOfFrames - 1;
				}
				else
					currentFrame = 0;
			}
		}

		float tempTime = -remainingFrameTime;
		remainingFrameTime = frames[currentFrame].duration - tempTime;
	}
}

void Animation::Render()
{
	if (!visible)
		return;
	SDL_Rect dstRect = { position.x,position.y,frames[currentFrame].texRect.w,frames[currentFrame].texRect.h };
	if (rotating || flip!=SDL_FLIP_NONE)
	{
		double finalAngle = 0.0f;
		if (rotating)
			finalAngle += angle;
		SDL_RenderCopyEx(&renderer, texture, &frames[currentFrame].texRect, &dstRect, finalAngle, &frames[currentFrame].origin, flip);
	}
	else
		SDL_RenderCopy(&renderer, texture, &frames[currentFrame].texRect, &dstRect);
}

bool Animation::Load(std::string dataPath, std::string texPath)
{
	LoadData(dataPath);
	LoadTexture(texPath);
	loaded = true;
	return true;
}

bool Animation::LoadData(std::string path)
{
	position = { 0,0 };
	angle = 0.0;
	flip = SDL_FLIP_NONE;

	// resource data
	//name.clear();
	//id = 0;

	// frame data
	LoadDataFromFile(path);
	//////////////////////////////////////////////////////////////////////
	//frames.clear();
	//frames.push_back(FrameData{ 0.1f,{ 0,0,64,205 },{ 32,103 } });
	//frames.push_back(FrameData{ 0.1f,{ 64,0,64,205 },{ 32,103 } });
	//frames.push_back(FrameData{ 0.1f,{ 128,0,64,205 },{ 32,103 } });
	//frames.push_back(FrameData{ 0.1f,{ 192,0,64,205 },{ 32,103 } });
	//////////////////////////////////////////////////////////////////////
	
	// header data
	numberOfFrames = (int)frames.size();
	currentFrame = 0;
	remainingFrameTime = frames[currentFrame].duration;

	// media player status
	loaded = false;
	play = false;
	loop = false;
	backwards = false;
	rotating = false;
	visible = true;
	playSpeed = 1.0;

	return true;
}

bool Animation::LoadTexture(std::string path)
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
	textureRect = { 0,0,surface->w,surface->h };

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

void Animation::Unload()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;

	position = { 0,0 };
	angle = 0.0;
	flip = SDL_FLIP_NONE;
	textureRect = { 0,0,0,0 };

	// resource data
	//name.clear();
	//id = 0;

	// header data
	numberOfFrames = 0;
	currentFrame = 0;
	remainingFrameTime = 0.0f;

	// frame data
	frames.clear();

	// media player status
	loaded = false;
	play = false;
	loop = false;
	backwards = false;
	rotating = false;
	visible = false;
	playSpeed = 1.0;
}

float Animation::GetDurationOfCurrentFrame()
{
	return frames[currentFrame].duration;
}

SDL_Rect Animation::GetRectOfCurrentFrame()
{
	return frames[currentFrame].texRect;
}

SDL_Point Animation::GetOriginOfCurrentFrame()
{
	return frames[currentFrame].origin;
}

void Animation::Play(bool loop, bool backwards, bool rotating, SDL_RendererFlip flip)
{
	play = true;
	this->loop = loop;
	this->backwards = backwards;
	this->rotating = rotating;
	this->flip = flip;
}

void Animation::Pause()
{
	play = false;
}

void Animation::Stop()
{
	play = false;
	currentFrame = 0;
	remainingFrameTime = frames[currentFrame].duration;
}

void Animation::NextFrame()
{
	currentFrame++;
	if (currentFrame >= numberOfFrames)
		currentFrame = 0;

	remainingFrameTime = frames[currentFrame].duration;
}

void Animation::PrevFrame()
{
	currentFrame--;
	if (currentFrame < 0)
		currentFrame = numberOfFrames - 1;

	remainingFrameTime = frames[currentFrame].duration;
}

void Animation::GotoFrame(int frameIndex)
{
	currentFrame = frameIndex;
	remainingFrameTime = frames[currentFrame].duration;
}

bool Animation::LoadDataFromFile(std::string path)
{
	frames.clear();
	//////////////////////////////////////////////////////////////////////
	//frames.push_back(FrameData{ 0.1f,{ 0,0,64,205 },{ 32,103 } });
	//frames.push_back(FrameData{ 0.1f,{ 64,0,64,205 },{ 32,103 } });
	//frames.push_back(FrameData{ 0.1f,{ 128,0,64,205 },{ 32,103 } });
	//frames.push_back(FrameData{ 0.1f,{ 192,0,64,205 },{ 32,103 } });
	//////////////////////////////////////////////////////////////////////

	std::ifstream infile(path);
	if (infile.is_open())
	{
		float duration;
		int texRectX;
		int texRectY;
		int texRectW;
		int texRectH;
		int originX;
		int originY;
		char c;
		while (infile >> duration >> c >> texRectX >> c >> texRectY >> c >> texRectW >> c >> texRectH >> c >> originX >> c >> originY && c == ',')
		{
			frames.push_back(FrameData{ duration, {texRectX,texRectY,texRectW,texRectH}, {originX,originY} });
		}
	}
	else
	{
		frames.clear();
		std::string message = "Could not read animation data from file: ";
		message.append(path);
		Error(message);
		return false;
	}
	infile.close();

	return true;
}
