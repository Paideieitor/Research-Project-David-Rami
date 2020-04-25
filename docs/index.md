# Assets ZIP Management wit PhysFS
## Description
As a game developer one wants to make his game as light as possible to avoid the player long downloads or loading screens, and most of this data comes very often from the
assets folders where images, sound files and 3D models take a lot of space. A very easy solution to this problem is to compress all this files and in this research I will
approach this solution using the PhysFS library in an SDL programm.
As a game developer one wants to make his game as light as possible to avoid the player long downloads or loading screens, and most of this data comes very often from the
assets folders where images, sound files and 3D models take a lot of space. A very easy solution to this problem is to compress all this files and in this research I will
approach this solution using the PhysFS library in an SDL program.
The objective of this research is to be able to run the program with all the needed assets in a compressed .zip file. This will make possible for the release folder to have the .dll, a single .zip with all the assets and the .exe to run the game.

## PhysFS
As for the library that I will be using, PhysFS, this is the description provided in their [web](https://icculus.org/physfs/):

“PhysicsFS is a library to provide abstract access to various archives. It is intended for use in video games, and the design was somewhat inspired by Quake 3's file subsystem. The programmer defines a "write directory" on the physical filesystem. No file writing done through the PhysicsFS API can leave that write directory, for security. For example, an embedded scripting language cannot write outside of this path if it uses PhysFS for all of its I/O, which means that untrusted scripts can run more safely. Symbolic links can be disabled as well, for added safety. For file reading, the programmer lists directories and archives that form a "search path". Once the search path is defined, it becomes a single, transparent hierarchical file system. This makes for easy access to ZIP files in the same way as you access a file directly on the disk, and it makes it easy to ship a new archive that will override a previous archive on a per-file basis.”

In this project I will make use of the following PhysFS functions (their descriptions are provided by the PhysFS main header physfs.h):

* PHYSFS_init(): Initialize the PhysicsFS library.
* PHYSFS_deinit(): Deinitialize the PhysicsFS library.
* PHYSFS_mount(const char* newDir, const char* mountPoint, int appendToPath ):  Add an archive or directory to the search path.
* PHYSFS_addToSearchPath(const char* newDir, int appendToPath): Add an archive or directory to the search path.
* PHYSFS_openRead(const char* filename):  Open a file for reading.
* PHYSFS_fileLength(PHYSFS_file* handle):  Get total length of a file in bytes.
* PHYSFS_read(PHYSFS_File* handle, void* buffer, PHYSFS_uint32 objSize, PHYSFS_uint32 objCount):  Read data from a PhysicsFS filehandle
* PHYSFS_close(PHYSFS_file* handle):  Close a PhysicsFS filehandle.
* PHYSFS_getLastErrorCode(): Get human-readable error information.
* PHYSFS_exists(const char *fname): Determine if a file exists in the search path.
## SDL
I will also be using SDL_RWops that allow the reading and writing of data in a stream without the caller needing to know where the data is coming from, which is perfect to read the buffers given by the PhysFS functions.
I will use the following RWops functions:

* IMG_Load_RW(SDL_RWops* src, int freesrc): This can load images from memory buffer. The image is load from src, if we want that src is automatically freed or closed we have to add an non-zero value in freesrc.
* Mix_LoadWAV_RW(SDL_RWops* src, int freesrc): This can load WAVE, AIFF, RIFF, OGG, and VOC formats from memory buffer. The sample is loaded from the src pointer. As the previous function, we can add a non-zero value in freesrc to close or free automatically src.
* Mix_LoadMUS_RW(SDL_RWops* src, int freesrc): This can load WAVE, MOD, MIDI, OGG, MP3, FLAC from memory buffer. Again, as functions mentioned before, src is the pointer that the sample is loaded from this and freesrc with a non-zero value is to free or close automatically.
* SDL_RWFromConstMem(const void* mem, int size): this prepares a read-only buffer memory buffer for use with SDL_RWops. mem is a pointer to a read-only buffer, size the buffer size in bytes.

## Structure
### Files

As I said before all the files are in a ZIP files (Assets.zip) inside there are 3 folders:
* audio: with a wav file in the fx subfolder
* data: with an xml file
* sprites: with 2 png images.

### Code

The files are managed by a module called AssetManager, that contains the following public functions:
* uint LoadData(const char* file, char** buffer) const: reads a file, saves all the read data in the buffer and returns the size of the read data.
* bool Exists(const char* file) const: returns true if the file exists, returns false elsewhere.
* SDL_RWops* Load(const char* file) const: loads the images and sound files from a memory buffer with SDL. This will be called inside the SDL_RWops functions.
* pugi::xml_parse_result LoadXML(pugi::xml_document &data_file, const char* path): returns a buffer with the data of the xml in the path, the data can be accessed using the xml_document passed.

## Handout
### TODO 1:
At first the Handout will crash because we are creating a path without initializing PhysFS. To solve this use the functions 
```
PHISFS_init(nullptr) 
``` 
and  
```
PHYSFS_deinit()
```
 in their corresponding places
### TODO 2:
Now we have to set the path from where to start searching all the other files in our case "Assets.zip". To solve this use the function 
```
PHYSFS_addToSearchPath("Assets.zip", 1)
```
### TODO 3: 
We have to open the loaded file to be read and after checking that it has been correctly opened, we need to allocate a buffer as big as the file.
### TODO 4:
We make sure that the file has been correctly read by checking if the read data is as big as the read file, then we return the data length and close the file, remember to delete the memory buffer if the read fails. 

To solve this 2 todos we can use this:
```
PHYSFS_file* data_file = PHYSFS_openRead(file);										

if (data_file != nullptr)
{
	int file_lenght = PHYSFS_fileLength(data_file);									
	*buffer = new char[(uint)file_lenght];											
	uint readed = PHYSFS_read(data_file, *buffer, 1, (uint)file_lenght);			
	if (readed != file_lenght)														
	{	
		LOG("Error while reading from file %s: %s\n", file, PHYSFS_getLastError());
		RELEASE(buffer);															
	}
	else
		ret = readed;																
			
	PHYSFS_close(data_file);														
}
else
	LOG("Error while opening file %s: %s\n", file, PHYSFS_getLastError());
```
### TODO 5:
Now that we can load files with PhysFS we have to use the SDL_RWops functions to load specific types of files in SDL to use them, in our case textures and sound effects. 
To solve this we go to Audio.cpp and in the LoadFx function substitute the function that loads a sound effect from the disk to 
```
Mix_Chunk* chunk = Mix_LoadWAV_RW(App->asset_manager->Load(path), 1)
```
 and in Textures.cpp in the Load function when loading a surface from the disk change the function to
```
SDL_Surface* surface = IMG_Load_RW(App->asset_manager->Load(path), 1)
``` 
