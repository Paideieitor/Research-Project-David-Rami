# Research Project by David Rami
## Description
As a game developer one wants to make his game as light as possible to avoid the player long downloads or loading screens, and most of this data comes very often from the
assets folders where images, sound files and 3D models take a lot of space. A very easy solution to this problem is to compress all this files and in this research I will
aproach this solution using the PhysFS library in an SDL programm.
As a game developer one wants to make his game as light as possible to avoid the player long downloads or loading screens, and most of this data comes very often from the
assets folders where images, sound files and 3D models take a lot of space. A very easy solution to this problem is to compress all this files and in this research I will
approach this solution using the PhysFS library in an SDL program.
The objective of this research is to be able to run the program with all the needed assets in a compressed .zip file. This will make possible for the release folder to have the .dll, a single .zip with all the assets and the .exe to run the game.

## PhysFS
As for the library that I will be using, PhysFS, this is the description provided in their web (https://icculus.org/physfs/):

“PhysicsFS is a library to provide abstract access to various archives. It is intended for use in video games, and the design was somewhat inspired by Quake 3's file subsystem. The programmer defines a "write directory" on the physical filesystem. No file writing done through the PhysicsFS API can leave that write directory, for security. For example, an embedded scripting language cannot write outside of this path if it uses PhysFS for all of its I/O, which means that untrusted scripts can run more safely. Symbolic links can be disabled as well, for added safety. For file reading, the programmer lists directories and archives that form a "search path". Once the search path is defined, it becomes a single, transparent hierarchical filesystem. This makes for easy access to ZIP files in the same way as you access a file directly on the disk, and it makes it easy to ship a new archive that will override a previous archive on a per-file basis.”

In this project I will make use of the following PhysFS functions (their descriptions are provided by the PhysFS main header physfs.h):

PHYSFS_init(): Initialize the PhysicsFS library.
PHYSFS_deinit(): Deinitialize the PhysicsFS library.
PHYSFS_mount(const char* newDir, const char* mountPoint, int appendToPath ):  Add an archive or directory to the search path.
PHYSFS_addToSearchPath(const char* newDir, int appendToPath): Add an archive or directory to the search path.
PHYSFS_openRead(const char* filename):  Open a file for reading.
PHYSFS_fileLength(PHYSFS_file* handle):  Get total length of a file in bytes.
PHYSFS_read(PHYSFS_File* handle, void* buffer, PHYSFS_uint32 objSize, PHYSFS_uint32 objCount):  Read data from a PhysicsFS filehandle
PHYSFS_close(PHYSFS_file* handle):  Close a PhysicsFS filehandle.
PHYSFS_getLastErrorCode(): Get human-readable error information.
PHYSFS_exists(const char *fname): Determine if a file exists in the search path.
## SDL
I will also be using SDL_RWops that allow the reading and writing of data in a stream without the caller needing to know where the data is coming from, which is perfect to read the buffers given by the PhysFS functions.
I will use the following RWops functions:

IMG_Load_RW(SDL_RWops* src, int freesrc): This can load images from memory buffer. The image is load from src, if we want that src is automatically freed or closed we have to add an non-zero value in freesrc.
Mix_LoadWAV_RW(SDL_RWops* src, int freesrc): This can load WAVE, AIFF, RIFF, OGG, and VOC formats from memory buffer. The sample is loaded from the src pointer. As the previous function, we can add a non-zero value in freesrc to close or free automatically src.
Mix_LoadMUS_RW(SDL_RWops* src, int freesrc): This can load WAVE, MOD, MIDI, OGG, MP3, FLAC from memory buffer. Again, as functions mentioned before, src is the pointer that the sample is loaded from this and freesrc with a non-zero value is to free or close automatically.
SDL_RWFromConstMem(const void* mem, int size): this prepares a read-only buffer memory buffer for use with SDL_RWops. mem is a pointer to a read-only buffer, size the buffer size in bytes.

##About Author

##Relevant Links
