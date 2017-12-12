/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * RUBIO Anthony and VIGNAUD Loïc wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return, Anthony R. and Loïc V.
 * ----------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "monster.h"
#include "image.h"
#include "menu.h"

using namespace std;

const int SCREEN_WIDTH=320;
const int SCREEN_HEIGHT=568;
const int SCREEN_BPP=32;

const int NBLEVEL= 5;

const int RESETR=26;
const int RESETCENTERX=93;
const int RESETCENTERY=531;


enum {MENU, GAME, CLOSE, PAUSE, END};                               //enum pour gérer les différents "états" du programme


int main()
{
    SDL_Surface *screen, *levelBackground, *levelWin, *menu, *endGame;
    SDL_Event event;                                                                        //Déclaration des surfaces et éléments (de type Element) necessaires
    Element awake, sleep, ice, book, arrowL, arrowR, arrowU, arrowD;
    string map= "map.txt";
    char a;
    bool find=false;
    int direction;
    int startLigne,startRow,endLine,endRow;
    int countEnd;

    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,
                            SCREEN_BPP,SDL_SWSURFACE);

    menu = load_image("title.bmp");
    levelBackground = load_image("background.bmp");
    levelWin= load_image("winSprite.bmp");                                                 //On affecte les images aux surfaces
    endGame= load_image("winEndSprite.bmp");
    awake.elem = loadImageWithColorKey("sprite.bmp",0,255,0);
    sleep.elem = loadImageWithColorKey("sprite.bmp",0,255,0);
    ice.elem = loadImageWithColorKey("sprite.bmp",0,255,0);
    book.elem = loadImageWithColorKey("sprite.bmp",0,255,0);
    arrowL.elem = loadImageWithColorKey("sprite.bmp",0,255,0);
    arrowR.elem = loadImageWithColorKey("sprite.bmp",0,255,0);
    arrowU.elem = loadImageWithColorKey("sprite.bmp",0,255,0);
    arrowD.elem = loadImageWithColorKey("sprite.bmp",0,255,0);



    int state = MENU;
    Level lvl;
    initElem(awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD);                             //Initialisation des différents éléments (application des rectangles de lectures aux surfaces)

    while(state!=CLOSE)
    {
        switch (state)
        {
        case MENU:  //Correspond au menu
            countEnd=0;
            a='a';                                      //On affecte à notre caractère 'a' le nom du premier niveau auquel on accède dés lancement du jeu
            while(state==MENU)
            {
                SDL_FillRect(screen,&screen->clip_rect,
                             SDL_MapRGB(screen->format,255,255,255));


                while(SDL_PollEvent(&event))
                {
                    if(event.type==SDL_QUIT)
                        state=CLOSE;
                }
                drawMenu(screen, menu);                         //on déssine le menu à l'écran
                state = (menuChoice(event));                 //On affecte à notre entier state la valeur retournée (GAME OU CLOSE) par la fonction qui gère le clique sur un bouton du menu
                SDL_Flip(screen);
            }
            break;

        case PAUSE: //Correspond à l'écran de gain de niveau
            applySurface(0,0,levelWin,screen,NULL);         //On affiche l'écran de niveau gagné
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_QUIT)
                    state=CLOSE;
                else if(event.type == SDL_MOUSEBUTTONDOWN){
                    a += 1;             //Si on clique avec la souris, le caractère du niveau s'incrémente pour passer au niveau suivant
                    state=GAME; //On repasse dans l'état du jeu avec le niveau suivant
                }
            }
            SDL_Flip(screen);
            break;

        case END:  //Ecran lorsque tous les niveaux sont complétés
            applySurface(0,0,endGame,screen,NULL);
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_QUIT)
                    state=CLOSE;
                else if(event.type == SDL_MOUSEBUTTONDOWN){
                    SDL_Delay(200);
                    state=MENU;         //Si on clique avec la souris on retourne au menu après un petit délais de 200 ms
                }
            }
            SDL_Flip(screen);
            break;


        case GAME: //Ecran de jeu
            file2Level(map, lvl, a);                    //On appelle la fonction qui affecte à notre matrice les données du fichier de niveau
            drawLevel(lvl, screen, awake, sleep, ice, book ,arrowL, arrowR, arrowU, arrowD, levelBackground);               //On dessine le niveau à partir des éléments et de la matrice
            SDL_Flip(screen);
            bool mouseButtonDown = false;

            while(state==GAME)
            {
                int startX, startY, endX=-1, endY = -1;
                SDL_FillRect(screen,&screen->clip_rect,
                             SDL_MapRGB(screen->format,255,255,255));

                while(SDL_PollEvent(&event))
                {

                    find=cursorOnMonster(lvl);   //On affecte à notre booléen le test si le curseur est sur un monstre à déplacer
                    if(event.type==SDL_QUIT)
                        state=CLOSE;
                    else if(event.type == SDL_MOUSEBUTTONDOWN && find)
                    {
                        mouseButtonDown = true;  //Si on clique et que l'on se trouve bien sur un monstre on affecte vrai au booléen qui gère le clique appuyé
                        SDL_GetMouseState(&startX, &startY);
                        startLigne=(startY-decalY)/(coefY);     //On récupère les coordonnées de la direction du curseur avec le clique appuyé
                        startRow=(startX-decalX)/(coefX);
                        endX = -1;
                        endY = -1;
                    }

                    else if(event.type == SDL_MOUSEBUTTONUP && mouseButtonDown){
                        mouseButtonDown = false; //Si on relache le bouton le booléen repasse à faux
                        SDL_GetMouseState(&endX, &endY);
                        endLine=(endY-decalY)/(coefY);          //On récupère la position où se trouve maintenant le curseur après avoir cliqué et relaché le clique
                        endRow=(endX-decalX)/(coefX);
                    }

                }

                if(endX != -1 && endY != -1){
                    if(endRow<startRow){  //Si la valeur de la colonne d'arrivée est inférieure à la colonne du départ alors il s'agit d'un mouvement gauche
                        direction=0;
                        monsterMovement(lvl, direction,startLigne,startRow, a, map, awake, sleep, ice, book, arrowL, arrowR, arrowU, arrowD, levelBackground, screen); //On appel la fonction qui gère le mouvement gauche
                        //mouvement gauche
                    }
                    else if(endRow>startRow){   //Si la valeur de la colonne d'arrivée est supérieure à la colonne du départ alors il s'agit d'un mouvement droite
                        direction=1;
                        monsterMovement(lvl, direction,startLigne,startRow, a, map, awake, sleep, ice, book, arrowL, arrowR, arrowU, arrowD, levelBackground, screen);
                        //mouvement droite
                    }
                    else if(endLine<startLigne){    //Si la valeur de la ligne d'arrivée est inférieure à la ligne du départ alors il s'agit d'un mouvement haut
                        direction=2;
                        monsterMovement(lvl, direction,startLigne,startRow, a, map, awake, sleep, ice, book, arrowL, arrowR, arrowU, arrowD, levelBackground, screen);
                        //mouvement haut
                    }
                    else if(endLine > startLigne){  //Si la valeur de la ligne d'arrivée est supérieure à la ligne du départ alors il s'agit d'un mouvement bas
                        direction=3;
                        monsterMovement(lvl, direction,startLigne,startRow, a, map, awake, sleep, ice, book, arrowL, arrowR, arrowU, arrowD, levelBackground, screen);
                        //mouvement bas
                    }
                    endX = -1;
                    endY = -1;

                    drawLevel(lvl, screen,awake,sleep,ice,book,arrowL, arrowR, arrowU, arrowD,levelBackground); //On redéssine le niveau après éventuel déplacement
                    SDL_Flip(screen);

                }

                int x;
                int y;
                SDL_GetMouseState(&x,&y);
                if(abs(RESETCENTERX-x)<=RESETR && abs(RESETCENTERY-y)<=RESETR && event.type == SDL_MOUSEBUTTONDOWN){    //Permet de reset le niveau si on clique sur le bouton
                    file2Level(map, lvl, a);
                    drawLevel(lvl, screen,awake,sleep,ice,book,arrowL, arrowR, arrowU, arrowD,levelBackground);     //Redéssine le niveau
                    SDL_Flip(screen);
                }

                if (scanLevel(lvl)==true && countEnd!=NBLEVEL)          //Test si le niveau est terminé
                {
                    SDL_Delay(800);
                    countEnd++;
                    state= PAUSE;           //Si oui on passe dans l'écran de transition avant le prochain niveau après un délai
                }

                if(countEnd==NBLEVEL){                  //Test si tous les niveaux sont terminés
                    SDL_Delay(800);
                    state= END;            //Si oui on passe à l'écran de fin de jeu après un délai
                }

            }
            break;

        }
    }
    SDL_FreeSurface(screen);
    SDL_FreeSurface(awake.elem);
    SDL_FreeSurface(sleep.elem);
    SDL_FreeSurface(ice.elem);
    SDL_FreeSurface(book.elem);
    SDL_FreeSurface(arrowL.elem);
    SDL_FreeSurface(arrowR.elem);
    SDL_FreeSurface(arrowU.elem);
    SDL_FreeSurface(arrowD.elem);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(levelWin);
    SDL_FreeSurface(levelBackground);
    SDL_FreeSurface(endGame);
    SDL_Quit();
    return EXIT_SUCCESS;
}

