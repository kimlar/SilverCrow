#pragma once

#include <SDL.h>
#include <vector>
#include <string>

struct FrameData
{
	float duration;
	SDL_Rect texRect;
	SDL_Point origin;
};

class Animation
{
public:
	Animation(SDL_Renderer& renderer);
	virtual ~Animation();

	void Update(float dt);
	void Render();

	bool Load(std::string dataPath, std::string texPath);
	bool LoadData(std::string path);
	bool LoadTexture(std::string path);
	void Unload();

	// geometry
	void SetPosition(int x, int y) { position.x = x; position.y = y; }
	SDL_Rect GetPosition() { return { position.x, position.y }; }
	void SetRotation(double angle) { this->angle = angle; }
	double GetRotation() { return angle; }

	// query current frame data
	float GetDurationOfCurrentFrame();
	SDL_Rect GetRectOfCurrentFrame();
	SDL_Point GetOriginOfCurrentFrame();

	// media player controls
	void Play(bool loop = true, bool backwards = false, bool rotating = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Pause();
	void Stop(); // stops playing and resets the position to start
	void NextFrame();
	void PrevFrame();
	void GotoFrame(int frameIndex);
	void SetPlaySpeed(double speed) { playSpeed = speed; }
	double GetPlaySpeed() { return playSpeed; }

	// other stuff
	void Show() { visible = true; }
	void Hide() { visible = false; }

	// Getters
	bool isPlaying() { return play; }
	bool isLooping() { return loop; }
	bool isBackwards() { return backwards; }

private:
	SDL_Renderer& renderer;
	SDL_Texture* texture = nullptr;
	SDL_Rect textureRect;
	SDL_Point position = { 0,0 };
	double angle = 0.0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	// resource manager data
	std::string name;
	int id = 0;

	// header data
	int numberOfFrames = 0;
	int currentFrame = 0;
	float remainingFrameTime = 0.0f;

	// frame data
	std::vector<FrameData> frames;

	// media player status
	bool loaded = false;
	bool play = false;
	bool loop = false;
	bool backwards = false;
	bool rotating = false;
	bool visible = false;
	double playSpeed = 1.0;

	// operations
	bool LoadDataFromFile(std::string path);
};
