#include<iostream>
#include"Application.h"

using namespace std;

Application* app = new Application();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	const int fps = 24;
	const int delay = 1000/fps;

	Uint32 frameStart;
	int frameTime;

	Uint32 wflags = SDL_WINDOW_BORDERLESS|SDL_WINDOW_ALWAYS_ON_TOP;
	Uint32 rflags = SDL_RENDERER_ACCELERATED;

	int desktopHeight = GetSystemMetrics(SM_CYSCREEN);
	int desktopWidth = GetSystemMetrics(SM_CXSCREEN);


	app->init("I'm bad at naming", desktopWidth, desktopHeight, 250, 250, wflags, rflags);
	while (app->isRunning) {

		frameStart = SDL_GetTicks();
		app->handle_input();
		app->update();
		app->render();
		frameTime = SDL_GetTicks() - frameStart;

		if (delay > frameTime) {
			SDL_Delay(delay - frameTime);
		}
	}
	app->cleanup();
	return 0;
}
