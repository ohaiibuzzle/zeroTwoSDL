#include"TextureLoader.h"

SDL_Texture* TextureLoader::Loader(const char* fn)
{
	Uint32 flag = IMG_INIT_PNG;
	if (IMG_Init(flag) != 0)
	{
		SDL_Texture* loadTxt = nullptr;
		SDL_Surface* tmpsf = IMG_Load(fn);
		loadTxt = SDL_CreateTextureFromSurface(Application::renderer,tmpsf);
		if (loadTxt)
		{
			return loadTxt;
		}
		else
		{
			printf("Something went wrong while loading: %s", fn);
			throw "TEXTURE_LOAD_ERROR";
		}
	}
	else
	{
		printf("Something went wrong while loading: %s", fn);
		throw "SDL_IMG_INIT_ERROR";
	}
}