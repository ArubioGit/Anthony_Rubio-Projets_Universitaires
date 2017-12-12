#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//Définition des prototypes de fonctions
void drawMenu(SDL_Surface *screen, SDL_Surface *menu);
int menuChoice(SDL_Event &event);

#endif // MENU_H
