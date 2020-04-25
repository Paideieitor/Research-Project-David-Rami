#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"


struct SDL_Texture;
struct SDL_Rect;
struct _TTF_Font;


class j1Scene : public j1Module
{
public:

	j1Scene();
	virtual ~j1Scene();

	bool Awake();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

private:
	
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Texture* textureXML;
	SDL_Rect rectXML;

	uint sound_effect;
};

#endif // __j1SCENE_H__