#ifndef __j1INPUT_H__
#define __j1INPUT_H__

#include "j1Module.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_gamecontroller.h"
#define NUM_MOUSE_BUTTONS 5
#define MAX_BUTTONS 10


struct SDL_Rect;

enum j1EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class j1Input : public j1Module
{

public:

	j1Input();
	virtual ~j1Input();

	bool Awake(pugi::xml_node&);

	bool Start();
	bool PreUpdate();

	bool CleanUp();

	bool GetWindowEvent(j1EventWindow ev);

	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	j1KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	bool GetWindowEvent(int code);

	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

private:
	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	SDL_Event ev;

	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;
};

#endif // __j1INPUT_H__