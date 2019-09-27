#include "Player.h"
#include "Texture.h"

Player::Player(SDL_Renderer& renderer) : renderer(renderer)
{
	posX = 0;
	posY = 0;
	velX = 0;
	velY = 0;
	rollShip = Roll::Center;
}

Player::~Player()
{

}

void Player::Create(std::string dataPath, std::string texPath, int x, int y)
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
}

void Player::Destroy()
{
	UnloadAnimation();
}

void Player::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY -= velocity;
			moveUp = true;
			break;
		case SDLK_DOWN:
			velY += velocity;
			moveDown = true;
			break;
		case SDLK_LEFT:
			velX -= velocity;
			moveLeft = true;
			break;
		case SDLK_RIGHT:
			velX += velocity;
			moveRight = true;
			break;
		case SDLK_LCTRL:
			fireAmmo = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY += velocity;
			moveUp = false;
			break;
		case SDLK_DOWN:
			velY -= velocity;
			moveDown = false;
			break;
		case SDLK_LEFT:
			velX += velocity;
			moveLeft = false;
			break;
		case SDLK_RIGHT:
			velX -= velocity;
			moveRight = false;
			break;
		case SDLK_LCTRL:
			fireAmmo = false;
			break;
		}
	}
}

void Player::SetPosition(int x, int y)
{
	posX = (float)x;
	posY = (float)y;
	animation->SetPosition(x,y);
}

void Player::Move(float dt)
{
	posX += velX * dt;

	if (posX < 0)
	{
		posX = 0;
	}
	else if (posX > (float)2560 - width) // 800=max map width
	{
		posX = (float)2560 - width;
	}

	posY += velY * dt;

	if (posY < 0)
	{
		posY = 0;
	}
	else if (posY > (float)1440 - height) // 600=max map height
	{
		posY = (float)1440 - height;
	}
}

void Player::Update(float dt)
{
	Move(dt);
	animation->SetPosition((int)posX, (int)posY);

	if (moveLeft && !moveRight)
		animation->GotoFrame(0);
	else if (!moveLeft && moveRight)
		animation->GotoFrame(2);
	else
		animation->GotoFrame(1);

	animation->Update(dt);


	UpdateAmmo(dt);
}

void Player::Render()
{
	SDL_Rect rect = { (int)posX, (int)posY, width, height };
	//SDL_RenderCopy(&renderer, texture, nullptr, &rect);
	animation->Render();
	RenderAmmo();
}

void Player::LoadAnimation(std::string dataPath, std::string texPath)
{
	animation = new Animation(renderer);
	animation->Load(dataPath, texPath);
	animation->SetPosition((int)posX, (int)posY);
}

void Player::UnloadAnimation()
{
	animation->Unload();
	delete animation;
	animation = nullptr;

	UnloadAmmo();
	delete ammoAnimation;
	ammoAnimation = nullptr;
}

void Player::LoadAmmo(std::string dataPath, std::string texPath)
{
	ammoAnimation = new Animation(renderer);
	ammoAnimation->Load(dataPath, texPath);
}

void Player::UnloadAmmo()
{
	ammoRects.clear();
	ammoAnimation->Unload();
}

void Player::FireAmmo()
{
	int leftWingX = (int)posX;
	int leftWingY = (int)posY + 50;
	int rightWingX = (int)posX + 100;
	int rightWingY = (int)posY + 50;

	ammoRects.push_back({ leftWingX, leftWingY, 7, 13 });
	ammoRects.push_back({ rightWingX, rightWingY, 7, 13 });
}

void Player::UpdateAmmo(float dt)
{
	fireTimeLeft -= dt;
	if (fireAmmo && fireTimeLeft <= 0.0f)
	{
		fireTimeLeft = fireRate;
		FireAmmo();
	}

	for (int i = 0; i < ammoRects.size(); i++)
		ammoRects[i].y -= (int)((float)(dt * fireVelocity));

	for (int i = 0; i < ammoRects.size(); i++)
	{
		if (ammoRects[i].y < 0)
			ammoRects.erase(ammoRects.begin() + i);
	}

	// collision check
	//..
}

void Player::RenderAmmo()
{
	for (int i = 0; i < ammoRects.size(); i++)
	{
		ammoAnimation->SetPosition(ammoRects[i].x, ammoRects[i].y);
		ammoAnimation->Render();
	}
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
