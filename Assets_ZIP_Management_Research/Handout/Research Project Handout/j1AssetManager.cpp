#include "p2Defs.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1AssetManager.h"
#include "PhysFS/include/physfs.h"
#include "SDL/include/SDL.h"

#pragma comment( lib, "PhysFS/lib/physfs.lib" )

j1AssetManager::j1AssetManager() : j1Module()
{
	name = ("asset_manager");

	//TODO 1: Initialize PhysFS

	CreatePath(".");		//Create a default path (uncomment when TODO 1 is complete)
}

j1AssetManager::~j1AssetManager()
{
	//TODO 1: Deinitialize PhysFS to close all the path and free memory
}

bool j1AssetManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Asset Manager");

	//TODO 2: Set the archive that we will search from

	return true;
}

bool j1AssetManager::CreatePath(const char* newDir, const char* mount_point)
{
	bool ret = true;
	
	if (PHYSFS_mount(newDir, mount_point, 1) == 0)		//Mount an archive file into the virtual filesystem
		LOG("Error: %s\n", PHYSFS_getLastError());
	else
		ret = false;

	return ret;
}

// Returns true if the file in path exists
bool j1AssetManager::Exists(const char* file) const
{
	return PHYSFS_exists(file);
}

//  Allocate needed bytes to a buffer and writes all data, returns size of the buffer
uint j1AssetManager::LoadData(const char* file, char** buffer) const
{
	uint ret = 0;

	//===========TODO 3===========
	//Open the file to read

	//Check the file has been read
	//Allocate a buffer of the size of the file

	//===========TODO 4===========
	//Read the data
	//Chech that the bytes read are the same as the file size

	//Delete the buffer

	//Return the amout of bytes read

	//Close the file handle
	
	return ret;
}

// Loads an image/fx/music from a memory buffer with SDL
SDL_RWops* j1AssetManager::Load(const char* file) const
{
	char* buffer;
	int size = LoadData(file, &buffer); //We get the size of the data and load it in a buffer

	if (size > 0)
	{
		SDL_RWops* r = SDL_RWFromConstMem(buffer, size); //We prepare a read-only buffer
		
		return r;
	}
	else
		return nullptr;
}

pugi::xml_parse_result j1AssetManager::LoadXML(pugi::xml_document &data_file, const char* path)
{
	char* buffer;
	uint file_size = App->asset_manager->LoadData(path, &buffer);
	pugi::xml_parse_result result = data_file.load_buffer(buffer, file_size); //We load the buffer as an immutable one
	RELEASE(buffer)

	return result;
}
