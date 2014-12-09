#include "map.h"

map::map()
{
	// This is the constructor
	// Don't forget to initialise those member variables!
	_texture = NULL;
	MapPosition_x = 0;
	MapPosition_y = 0;
}

map::~map()
{
	// This is the destructor
	// Use SDL to clean up our texture 
	if (_texture)
	{
		SDL_DestroyTexture(_texture);
	}
}

bool map::LoadFromPNG(std::string filename, SDL_Renderer *renderer)
{
	//A check for whether the file name is empty
	if (filename.empty())
	{
		std::cerr << "ERROR: map::LoadFromPNG - empty filename given" << std::endl;
		return false;
	}

	// First we load it to what SDL calls a 'surface'
	// This is just a raw collection of pixels
	SDL_Surface * image = IMG_Load(filename.c_str());
	if (!image)
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		std::cerr << "ERROR: map::LoadFromPNG - Can't find the image file." << std::endl;
		return false;
	}

	// Next we convert the SDL_Surface into what it calls a 'texture'
	// This is kinda similar, but because it's bound to a renderer, SDL can make some useful optimisations behind the scenes
	// This will make it draw to the screen faster
	_texture = SDL_CreateTextureFromSurface(renderer, image);


	// We've now finished with our raw pixel data, so we can get rid of it
	SDL_FreeSurface(image);

	return true;
}

void map::Draw(int SPosition_x, int SPosition_y, SDL_Renderer *renderer)
{
	// This will specify where to draw the sprite
	SDL_Rect destRect;
	// SDL has (0,0) at the top left corner - check this by playing about with the numbers!
	destRect.x = SPosition_x;
	destRect.y = SPosition_y;



	// Query the texture to get its original width and height
	SDL_QueryTexture(_texture, NULL, NULL, &destRect.w, &destRect.h);

	// Here we are telling the renderer to copy the texture memory to our screen,
	// at the position of the rectangle we specify
	// The parameter that's currently NULL can be used to specify another rectangle that's a sub-region of the whole image
	// This is for doing sprite animation type effects
	SDL_RenderCopy(renderer, _texture, NULL, &destRect);
}