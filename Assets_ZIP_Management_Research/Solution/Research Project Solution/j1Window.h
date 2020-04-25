#ifndef __j1WINDOW_H__
#define __j1WINDOW_H__

#include "j1Module.h"
#include <string>
struct SDL_Window;
struct SDL_Surface;

class j1Window : public j1Module
{
public:

	j1Window();
	virtual ~j1Window();

	bool Awake(pugi::xml_node&);

	bool CleanUp();

	void SetTitle(const char* new_title);

	void GetWindowSize(uint& width, uint& height) const;

	uint GetScale() const;

	SDL_Window* window;
	SDL_Surface* screen_surface;

	std::string	title;
	uint		width;
	uint		height;
	uint		scale;
};

#endif // __j1WINDOW_H__