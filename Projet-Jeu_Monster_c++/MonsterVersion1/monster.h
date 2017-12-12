//#ifndef MONSTER_H
#define MONSTER_H

#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <iostream>
#include <cstdlib>
#include <array>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>



//Constantes
const int NB_MAX_MONSTER = 45;
const int NB_ROW=5;
const int NB_LINE=9;

const int decalX=21;
const int decalY=32;
const int coefX=58;
const int coefY=52;

using Level=std::array<std::array<int,NB_ROW>,NB_LINE>;

// Définitions des structures
struct Element
{
    SDL_Surface *elem;
    SDL_Rect read_elem;
};

//Définitions des prototypes de fonctions pour le level
bool scanLevel(Level & lvl);
void drawLevel(Level lvl, SDL_Surface *screen, Element awake, Element sleep, Element ice, Element book, Element arrowL, Element arrowR, Element arrowU, Element arrowD, SDL_Surface *levelSurface);
//Définitions des prototypes de fonctions
void initElem(Element &awake, Element &sleep, Element &ice, Element &book, Element &arrowL, Element &arrowR, Element &arrowU, Element &arrowD);
bool cursorOnMonster(Level lvl);
void monsterMovement(Level &lvl, int direction, int i, int j, char a, std::string map, Element awake, Element sleep, Element ice, Element book, Element arrowL, Element arrowR, Element arrowU, Element arrowD, SDL_Surface *levelSurface, SDL_Surface *screen);
void file2Level(std::string fichier, Level &lvl, char a);


#endif // MONSTER_H
