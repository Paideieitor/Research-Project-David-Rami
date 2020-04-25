#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1AssetManager.h"
#include <list>
#include <string>

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

j1Textures::j1Textures() : j1Module()
{
	name.assign("textures");
}

j1Textures::~j1Textures()
{}

bool j1Textures::Awake(pugi::xml_node& config)
{
	LOG("Init Image library");
	bool ret = true;

	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}
	return ret;
}

bool j1Textures::Start()
{
	LOG("Start Textures");
	bool ret = true;
	return ret;
}

bool j1Textures::CleanUp()
{
	LOG("Freeing textures and Image library");


	for (std::list<SDL_Texture*>::iterator item = textures.begin(); item != textures.end(); ++item) {
		SDL_DestroyTexture(*item);
	}

	textures.clear();
	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const j1Textures::Load(const char* path)
{
	SDL_Texture* texture = NULL;
	//TODO 5: We need a method that reads from the memory buffer instead of the disk
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

bool j1Textures::UnLoad(SDL_Texture* texture)
{

	for (std::list<SDL_Texture*>::iterator item = textures.begin(); item != textures.end(); ++item) {
		if (texture == *item)
		{
			SDL_DestroyTexture(*item);
			textures.erase(item);
			return true;
		}
	}



	return false;
}

SDL_Texture* const j1Textures::LoadSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

	if (texture == NULL)
	{
		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		textures.push_back(texture);
	}

	return texture;
}

void j1Textures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*)&width, (int*)&height);
}