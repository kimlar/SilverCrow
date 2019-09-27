#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "PointerBag.h"

//
// TODO:
//	* Do not use hard coded values for window width and height. Obtain it & apply it.
//

class Window
{
public:
	Window(PointerBag* pointerBag);
	~Window();

	void Create();
	void Destroy();

	void ClearScreen();
	void UpdateScreen();

	void HandleEvent(SDL_Event& e);

	// Operators
	void SetFullScreen(bool fullscreen, bool exclusive = false);

	// Getters
	SDL_Window& GetWindow() { return *window; }
	SDL_Renderer& GetRenderer() { return *renderer; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetRefreshRate() { return refreshRate; }
	bool isFullScreen() { return fullScreen; }
	bool isMinimized() { return minimized; }
	bool hasKeyboardFocus() { return keyboardFocus; }
	bool hasMouseFocus() { return mouseFocus; }

	// Delta time
	float GetDT() { return dt; }
private:
	PointerBag* pointerBag = nullptr;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int width;
	int height;
	int refreshRate;

	float dt;

	bool fullScreen;
	bool useExclusiveFullscreen;
	bool minimized;
	bool keyboardFocus;
	bool mouseFocus;
};
