#include"Application.h"

SDL_Renderer* Application::renderer = nullptr;
SDL_Window* window = nullptr;
Character* chr;

void Application::init(const char* title, int x, int y, int w, int h, Uint32 windowflags, Uint32 rendererflags) {

	int taskheight = getWorkArea();

	std::cout << taskheight << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL Started" << std::endl;
		window = SDL_CreateWindow(title, x-250, y-250-taskheight, w, h, windowflags);

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Texture filtering not enabled!");
		}

		if (window)
		{
			std::cout << "Window created" << std::endl;
			renderer = SDL_CreateRenderer(window, -1, rendererflags);
			if (renderer)
			{
				std::cout << "Initialization complete" << std::endl;
				SDL_SetRenderDrawColor(renderer, 0, 0, 139, 255);
				isRunning = true;
			}
			else
			{
				printf("Something wrong! %s \n", SDL_GetError());
			}
		}
		else
		{
			printf("Something wrong! %s \n", SDL_GetError());
		}
	}
	else
	{
		printf("Something wrong! %s \n", SDL_GetError());
	}

	int code = Mix_Init(MIX_INIT_MP3);
	if (!(code & MIX_INIT_MP3))
	{
		throw "Audio error!";
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
		throw "Audio init error!";
	}

	srand(time(NULL));

	Application::MakeWindowTransparent(window, RGB(0, 0, 139));

	chr = new Character("assets\\002.png", w-200, h-200, "assets\\sound\\");
	
}

int Application::getWorkArea()
{
	RECT rect;
	HWND taskBar = FindWindow(L"Shell_traywnd", NULL);
	if (taskBar && GetWindowRect(taskBar, &rect)) {
		return rect.bottom - rect.top;
	}
	else return 0;
}

void Application::handle_input() {
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case (SDL_QUIT):
	{
		isRunning = false;
		break;
	}
	case (SDL_KEYDOWN):
	{
		switch (event.key.keysym.sym)
		case (SDLK_ESCAPE):
		{
		{
			isRunning = false;
		}
		default:
			break;
		}
	}
	case (SDL_MOUSEBUTTONDOWN):
	{
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
		{
			chr->onClick();
		}
		}
	}
	default:
		break;
	}

}

bool Application::MakeWindowTransparent(SDL_Window* window, COLORREF colorKey) {
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
	SDL_GetWindowWMInfo(window, &wmInfo);
	HWND hWnd = wmInfo.info.win.window;

	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	return SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}

void Application::update(){
	chr->update();
}

void Application::render() {
	SDL_RenderClear(renderer);

	chr->render();

	SDL_RenderPresent(renderer);
}

void Application::cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}