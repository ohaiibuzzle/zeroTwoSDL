#include"Character.h"
namespace fs = std::filesystem;

Character::Character(const char* textpath, int x, int y, const char* soundpath)
{
	music = NULL;
	delay = 1;
	laststamp = time(NULL);

	std::string path = soundpath;
	for (const auto& entry : fs::directory_iterator(path))
	{
		soundfx.push_back(entry.path().string());
	}

	std::cout << soundfx.size() << std::endl;

	charTxt = TextureLoader::Loader(textpath);

	src.x = src.y = 0;
	src.h = src.w = 400;
	
	dest.x = x;
	dest.y = y;

	dest.w = dest.h = 200;

}

Character::~Character() {
	Mix_FreeMusic(music);
	std::cout << "Goodbye!" << std::endl;
}

void Character::render()
{
	SDL_RenderCopy(Application::renderer, charTxt, NULL, &dest);
}

void Character::update()
{
	//TODO
}

void Character::playFx() {

	const char* filename = soundfx[rand() % soundfx.size()].c_str();
	std::cout << filename << std::endl;

	music = Mix_LoadMUS(filename);

	if (music == NULL) throw "File Error!";

	if (Mix_PlayMusic(music, 1) == -1) printf("Music error: %s", Mix_GetError());

}

void Character::onClick()
{
	long now = time(NULL);
	if (now - laststamp >= delay)
	{
		playFx();
		std::cout << "Click!" << std::endl;
		laststamp = now;
	}
}