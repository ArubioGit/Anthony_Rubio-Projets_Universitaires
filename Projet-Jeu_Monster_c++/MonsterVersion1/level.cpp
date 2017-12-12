
using namespace std;
#include "monster.h"
#include "image.h"
#include <fstream>

const int SPRITEADJUST=10;

/****************** Nom de la fonction **********************
* scanLevel                                                 *
******************** Auteur , Dates *************************
* VIGNAUD Loïc - 10/12/2016                                *
********************* Description ***************************
* La fonction "scan" le niveau pour vérifier s'il y reste   *
* un monstre endormi (utile pour gérer l'achèvement d'un    *
* niveau)                                                   *
*********************** Entrées *****************************
* La fonction prend en entrée une matrice (type Level)      *
*********************** Sorties *****************************
* La fonction renvoie un booléen passé à faux s'il reste au *
* moins un monstre endormi et renvoie vrai s'il n'en reste  *
* aucun
************************************************************/
bool scanLevel(Level & lvl)
{
    int l=0;
    int c;
    bool sleepingMonster = false;
    while(l<NB_LINE && !sleepingMonster)            //On "scan" le niveau
    {
        c=0;
        while (c<NB_ROW && !sleepingMonster)
        {
            if (lvl[l][c]==2)
            {
                sleepingMonster=true;           //Renvoie un booléen qui vaut vrai s'il ne reste plus de monstre endormi dans le niveau
            }
            c++;
        }
        l++;
    }
    return !sleepingMonster;
}

/****************** Nom de la fonction **********************
* fichier2Level                                             *
******************** Auteur , Dates *************************
* VIGNAUD Loic - 08/12/2016                                 *
********************* Description ***************************
* La fonction remplie la matrice à partir d'un fichier pris *
* en paramètre.
*********************** Entrées *****************************
* La fonction prend une chaine de caractère en paramètre   *
* pour le fichier ainsi que notre matrice de type Level et  *
* un charactère a.
*********************** Sorties *****************************
* Etant une action (void) la fonction ne revoie rien.       *
************************************************************/
void file2Level(string file, Level &lvl, char a)
{
    fstream f;
    string s="";
    string reach = "#";
    reach += a;  // On declare une chaine de caractère "#a" (on incrementera a pour changer de zone la tete de lecture et donc changer de niveau)

    f.open( file.c_str(), ios::in );
    if( f.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    while (s != reach) // On déplace la tete de lecture jusqu'au niveau que l'on veut jouer
    {
        f >> s;
    }
    for( int i=0; i<NB_LINE; i++ )
        for( int j=0; j<NB_ROW; j++ )
            f >> lvl[i][j];    // On rentre chaque entier lu dans le fichier afin de le mettre dans la matrice case par case.
    f.close();
}

/****************** Nom de la fonction **********************
* dessineLevel                                              *
******************** Auteur , Dates *************************
* RUBIO Anthony, VIGNAUD Loic - 21/11/2016                  *
********************* Description ***************************
* Cette fonction dessine le niveau "graphiquement" par       *
* blit (applySurface) des différents éléments qui composent  *
* la matrice sur la grille de jeu
*********************** Entrées *****************************
* La fonction prend en entrée une matrice, une surface      *
* écran et les différents élements (monstre eveillé,        *
* monstre endormi, glace, livre, fleche) de type Element    *
* (voir structure Element)
*********************** Sorties *****************************
* Etant une action, la fonction ne revoie rien              *
************************************************************/
void drawLevel(Level lvl, SDL_Surface *screen, Element awake, Element sleep, Element ice, Element book, Element arrowL, Element arrowR, Element arrowU, Element arrowD, SDL_Surface *levelSurface)
{

    int a,b;

    applySurface(0,0,levelSurface,screen,NULL);

    for (int i=0; i < NB_LINE ;i++)         //On parcourt la matrice
    {
        for (int j=0 ;j < NB_ROW; j++)
        {
            a=(j*coefX)+decalX;         //Calcul permettant de faire correspondre la grille du jeu avec la matrice par proportionnalité. (voir explication du rapport)
            b=(i*coefY)+decalY;
            switch (lvl[i][j])
            {
            case 0 :
                ;
                break;
            case 1 : //Monstre éveillé
                applySurface(a,b,awake.elem,screen,&awake.read_elem); //Si on croise un 1 dans la matrice on applique un monstre éveillé à la postion actuel

                break;
            case 2 : //Monstre Endormi
                applySurface(a,b-SPRITEADJUST,sleep.elem,screen,&sleep.read_elem);
                ;
                break;
            case 3 : //Livre
                applySurface(a-SPRITEADJUST,b-SPRITEADJUST,book.elem,screen,&book.read_elem);
                ;
                break;
            case 4: //Glace
                applySurface(a-SPRITEADJUST,b-SPRITEADJUST,ice.elem,screen,&ice.read_elem);
                ;
                break;
            case 5: //Fleche GAUCHE
                applySurface(a,b,arrowL.elem,screen,&arrowL.read_elem);
                ;
                break;
            case 6: //Fleche DROITE
                applySurface(a,b,arrowR.elem,screen,&arrowR.read_elem);
                ;
                break;
            case 7: //Fleche HAUT
                applySurface(a,b,arrowU.elem,screen,&arrowU.read_elem);
                ;
                break;
            case 8: //Fleche BAS
                applySurface(a,b,arrowD.elem,screen,&arrowD.read_elem);
                ;
                break;
            default :
                cout << "erreur d'affichage ou rien à afficher" << endl;
                ;
            }
        }
    }
    SDL_Flip(screen);
}


