#pragma once

#include <SDL.h>
#include <string>
#include <vector>

#include "Animation.h"

class Enemy
{
public:
	enum class Roll { Left = 0, Center, Right };

	Enemy(SDL_Renderer& renderer);
	virtual ~Enemy();

	void Create(std::string dataPath, std::string texPath, int x, int y);
	void Destroy();

	//void HandleEvent(SDL_Event& e);
	void SetPosition(int x, int y);
	void Move(float dt);

	void Update(float dt);
	void Render();

	//void LoadTexture(std::string path);
	//void UnloadTexture();

	void LoadAnimation(std::string dataPath, std::string texPath);
	void UnloadAnimation();
	Animation& GetAnimation() { return *animation; }

	Roll rollShip = Roll::Center;

private:
	SDL_Renderer& renderer;
	//SDL_Texture* texture;
	Animation* animation;
	int width;
	int height;

	float posX;
	float posY;
	float velX;
	float velY;

	const int velocity = 40;

	// Controller
	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;
	bool fireAmmo;

	// Weapon
	void LoadAmmo(std::string dataPath, std::string texPath);
	void UnloadAmmo();
	void FireAmmo();
	void UpdateAmmo(float dt);
	void RenderAmmo();
	Animation* ammoAnimation;
	std::vector<SDL_Rect> ammoRects;
	float fireRate;
	float fireTimeLeft;
	float fireVelocity;

	// AI
	void UpdateAI(float dt);
	void HandleControl();
	float sinusMoveTime;
};
