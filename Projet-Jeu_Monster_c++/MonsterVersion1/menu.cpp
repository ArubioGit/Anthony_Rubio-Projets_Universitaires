
#include "image.h"
#include "menu.h"
using namespace std;

const int PLAYR=47;
const int PLAYCENTERX=150;
const int PLAYCENTERY=312;

const int QUITR=18;
const int QUITCENTERX=25;
const int QUITCENTERY=24;

/****************** Nom de la fonction **********************
* dessinerMenu                                              *
******************** Auteur , Dates *************************
* RUBIO Anthony - 23/11/2016                                *
********************* Description ***************************
* La fonction affiche le menu du jeu à son lancement        *
*********************** Entrées *****************************
* La fonction prend en entrée une surface écran             *
*********************** Sorties *****************************
* Etant une action la fonction ne renvoie rien              *
************************************************************/
void drawMenu(SDL_Surface *screen, SDL_Surface *menu)
{
    applySurface(0,0,menu,screen,NULL);

    SDL_Flip(screen);

}


/****************** Nom de la fonction **********************
* menuChoice                                                *
******************** Auteur , Dates *************************
* RUBIO Anthony - 21/11/2016                                *
********************* Description ***************************
* Cette fonction permet de lancer le jeu en cliquant sur le *
* bouton play ou de le quitter en cliquant sur la croix
*********************** Entrées *****************************
* La fonction prend un SDL_event en entrée (pour pouvoir ici *
* utiliser les event de clique de souris)
*********************** Sorties *****************************
* La fonction renvoie un entier (enum)                      *
************************************************************/
int menuChoice(SDL_Event &event)
{
    enum {MENU, GAME, CLOSE};
    int state=MENU;
    int x;
    int y;
    SDL_GetMouseState(&x,&y);  //On vérifie les coordonnées du curseur

    if(abs(PLAYCENTERX-x)<=PLAYR && abs(PLAYCENTERY-y)<=PLAYR && event.type == SDL_MOUSEBUTTONDOWN)         //Si on se trouve sur le bouton play et que l'on clique on lance le jeu
    {
        state = GAME;
    }

    if(abs(QUITCENTERX-x)<=QUITR && abs(QUITCENTERY-y)<=QUITR && event.type == SDL_MOUSEBUTTONDOWN)         //Si on se trouve sur la croix pour quitter et que l'on clique on quitte le jeu
    {
        state = CLOSE;
    }
    return state;

}
