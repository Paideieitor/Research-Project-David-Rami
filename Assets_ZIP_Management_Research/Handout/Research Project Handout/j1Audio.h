#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "j1Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include <list>

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class j1Audio : public j1Module
{
public:

	j1Audio();
	virtual ~j1Audio();

	bool Awake(pugi::xml_node&);

	bool Update(float dt);
	bool CleanUp();

	unsigned int LoadFx(const char* path);

	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	bool PlayFx(unsigned int fx, int repeat = 0);

private:
	
	_Mix_Music *music;
	std::list<Mix_Chunk*> fx;

	pugi::xml_node fx_node;
};

#endif // __j1AUDIO_H__