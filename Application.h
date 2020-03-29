#pragma once
#include<iostream>
#include<SDL.h>
#undef main
#include<SDL_syswm.h>
#include<SDL_mixer.h>
#include<Windows.h>
#include"TextureLoader.h"
#include"Character.h"
#include"TextureLoader.h"
#include<vector>
#include<string>

class Application {
private:
	SDL_Event event;
	SDL_Window* window;
	
public:
	static SDL_Renderer *renderer;

	bool MakeWindowTransparent(SDL_Window* window, COLORREF colorKey);
	void init(const char* title, int x, int y, int w, int h, Uint32 windowflags, Uint32 rendererflags);
	void cleanup();
	void handle_input();
	void render();
	void update();

	int getWorkArea();

	bool isRunning;
};