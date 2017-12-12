
#include "image.h"
#include <iostream>
using namespace std;

//FONCTIONS

/****************** Nom de la fonction **********************
* loadImageWithColorKeY                                     *
******************** Auteur , Dates *************************
* Equipe Pedagogique - Date inconnue                        *
********************* Description ***************************
* La fonction charge une image en mémoire en lui            *
* appliquant un colorkey (rendre invisible une couleur de   *
* l'image (utilise pour un sprite)
*********************** Entrées *****************************
* La fonction prend en entrée une chaine de caractère pour  *
* nom du fichier et 3 entiers pour gérer les couleurs        *
*********************** Sorties *****************************
* La fonction renvoie une surface contenant l'image         *
************************************************************/
SDL_Surface * loadImageWithColorKey(string filename, int r, int g, int b)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );

        //If the image was optimized just fine
        if( optimizedImage != NULL )
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, r, g, b );

            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
    //Return the optimized image
    return optimizedImage;
}

/****************** Nom de la fonction **********************
* load_image                                                *
******************** Auteur , Dates *************************
* Equipe pédagogique - date inconnue                        *
********************* Description ***************************
* La fonction charge une image en mémoire                   *
*********************** Entrées *****************************
* La fonction prend en entrée une chaine de caractère       *
*********************** Sorties *****************************
* La fonction renvoie une surface (contenant l'image)       *
************************************************************/
SDL_Surface *load_image( string filename )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    //Return the optimized image
    return optimizedImage;
}

/****************** Nom de la fonction **********************
* applySurface                                              *
******************** Auteur , Dates *************************
* Equipe Pédagogique - Date inconnue                       *
********************* Description ***************************
* Cette fonction applique (blit) une surface passée en      *
* paramètre sur une autre.
*********************** Entrées *****************************
* La fonction prend en entrée deux entiers x et y, une       *
* surface source, une surface destination et un rectangle de*
* lecture.
*********************** Sorties *****************************
* Etant une action, cette fonction ne renvoie rien.         *
************************************************************/
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}









