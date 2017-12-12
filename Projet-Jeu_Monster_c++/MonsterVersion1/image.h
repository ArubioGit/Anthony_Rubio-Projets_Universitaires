#ifndef IMAGE_H
#define IMAGE_H

#endif // IMAGE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>



SDL_Surface *load_image( std::string filename );
SDL_Surface * loadImageWithColorKey(std::string filename, int r, int g, int b);
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

