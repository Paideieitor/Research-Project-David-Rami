#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"

#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1AssetManager.h"

#include <string>

j1Scene::j1Scene() : j1Module()
{
	name.assign("scene");

}

j1Scene::~j1Scene()
{}

bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool j1Scene::Start()
{
	bool ret = true;
	
	rect = { 0, 0, 1280, 720 };
	rectXML = { 0,0,101,161 };

	texture = App->tex->Load("sprites/logo.png");

	pugi::xml_document data_file;
	pugi::xml_parse_result result = App->asset_manager->LoadXML(data_file, "data/image_data.xml");
	pugi::xml_node attributes = data_file.child("data").child("texture");
	textureXML = App->tex->Load(attributes.attribute("file").as_string());

	sound_effect = App->audio->LoadFx("audio/fx/logo_intro.wav");

	App->audio->PlayFx(sound_effect);

	return ret;
}

bool j1Scene::Update(float dt)
{
	App->render->Blit(texture, 0, 0, &rect, false);		//Blit the textures
	App->render->Blit(textureXML, 0, 0, &rectXML, false);

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		App->audio->PlayFx(sound_effect);				//Play the SFX

	return true;
}

bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
