#pragma once
#include"Application.h"
#include<filesystem>

class Character
{
public:
	Character(const char* textpath, int x, int y, const char* soundpath);
	~Character();

	void render();
	void update();
	void onClick();

	void playFx();

private:
	long laststamp;
	std::vector<std::string> soundfx;
	int delay;
	SDL_Texture* charTxt;
	SDL_Rect src, dest;
	Mix_Music* music;
};