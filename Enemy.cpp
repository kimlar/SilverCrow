#include "Enemy.h"

#include <cmath>
#include "Texture.h"

Enemy::Enemy(SDL_Renderer& renderer) : renderer(renderer)
{
	posX = 0;
	posY = 0;
	velX = 0;
	velY = 0;
	rollShip = Roll::Center;
}

Enemy::~Enemy()
{

}

void Enemy::Create(std::string dataPath, std::string texPath, int x, int y)
{
	LoadAnimation(dataPath, texPath);
	SetPosition(x, y);
	rollShip = Roll::Center;

	LoadAmmo("ammo-P117.txt", "ammo-P117.png");
	fireRate = 0.2f;
	fireTimeLeft = 0.0f;
	fireVelocity = 500.0f;

	// Controller
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
	fireAmmo = false;

	sinusMoveTime = 0.0f;
}

void Enemy::Destroy()
{
	UnloadAnimation();
}

void Enemy::SetPosition(int x, int y)
{
	posX = (float)x;
	posY = (float)y;
	animation->SetPosition(x, y);
}

void Enemy::Move(float dt)
{
	posX += velX * dt;

	if (posX < 0)
	{
		posX = 0;
	}
	else if (posX >(float)2560 - width) // 800=max map width
	{
		posX = (float)2560 - width;
	}

	posY += velY * dt;

	if (posY < 0)
	{
		posY = 0;
	}
	else if (posY >(float)1440 - height) // 600=max map height
	{
		posY = (float)1440 - height;
	}
}

void Enemy::Update(float dt)
{
	UpdateAI(dt);

	Move(dt);
	animation->SetPosition((int)posX, (int)posY);

	/*
	if (moveLeft && !moveRight)
		animation->GotoFrame(0);
	else if (!moveLeft && moveRight)
		animation->GotoFrame(2);
	else
		animation->GotoFrame(1);
	*/

	animation->Update(dt);


	UpdateAmmo(dt);
}

void Enemy::Render()
{
	SDL_Rect rect = { (int)posX, (int)posY, width, height };
	//SDL_RenderCopy(&renderer, texture, nullptr, &rect);
	animation->Render();
	RenderAmmo();
}

void Enemy::LoadAnimation(std::string dataPath, std::string texPath)
{
	animation = new Animation(renderer);
	animation->Load(dataPath, texPath);
	animation->SetPosition((int)posX, (int)posY);
}

void Enemy::UnloadAnimation()
{
	animation->Unload();
	delete animation;
	animation = nullptr;

	UnloadAmmo();
	delete ammoAnimation;
	ammoAnimation = nullptr;
}

void Enemy::LoadAmmo(std::string dataPath, std::string texPath)
{
	ammoAnimation = new Animation(renderer);
	ammoAnimation->Load(dataPath, texPath);
}

void Enemy::UnloadAmmo()
{
	ammoRects.clear();
	ammoAnimation->Unload();
}

void Enemy::FireAmmo()
{
	int leftWingX = (int)posX;
	int leftWingY = (int)posY + 50;
	int rightWingX = (int)posX + 100;
	int rightWingY = (int)posY + 50;

	ammoRects.push_back({ leftWingX, leftWingY, 7, 13 });
	ammoRects.push_back({ rightWingX, rightWingY, 7, 13 });
}

void Enemy::UpdateAmmo(float dt)
{
	fireTimeLeft -= dt;
	if (fireAmmo && fireTimeLeft <= 0.0f)
	{
		fireTimeLeft = fireRate;
		FireAmmo();
	}

	for (int i = 0; i < ammoRects.size(); i++)
		ammoRects[i].y += (int)((float)(dt * fireVelocity));

	for (int i = 0; i < ammoRects.size(); i++)
	{
		if (ammoRects[i].y > 1440)
			ammoRects.erase(ammoRects.begin() + i);
	}

	// collision check
	// ...
}

void Enemy::RenderAmmo()
{
	for (int i = 0; i < ammoRects.size(); i++)
	{
		ammoAnimation->SetPosition(ammoRects[i].x, ammoRects[i].y);
		ammoAnimation->Render();
	}
}

void Enemy::UpdateAI(float dt)
{
	sinusMoveTime += dt;
	int gotoX = (int)std::sin(sinusMoveTime);

	if ((posX - 400) > gotoX)
	{
		moveLeft = true;
		moveRight = false;
	}
	else if ((posX - 400) < gotoX)
	{
		moveLeft = false;
		moveRight = true;
	}

	fireAmmo = true;

	HandleControl();
}

void Enemy::HandleControl()
{
	if (moveLeft)
		velX -= velocity;
	else
		velX += velocity;

	if (moveRight)
		velX += velocity;
	else
		velX -= velocity;
}

/*
void Player::LoadTexture(std::string path)
{
Texture* texture = new Texture(renderer);
texture->Load(path);
this->texture = &texture->GetTexture();
width = texture->GetWidth();
height = texture->GetHeight();
delete texture;
texture = nullptr;
}

void Player::UnloadTexture()
{
SDL_DestroyTexture(texture);
texture = nullptr;
}
*/
