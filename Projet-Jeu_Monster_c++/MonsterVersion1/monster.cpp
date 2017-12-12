#include "monster.h"
using namespace std;

const int AWAKE_POSX_RECT=6;
const int AWAKE_POSY_RECT=6;
const int AWAKE_HEIGHT_RECT=48;
const int AWAKE_WIDTH_RECT=45;

const int SLEEP_POSX_RECT=65;
const int SLEEP_POSY_RECT=0;
const int SLEEP_HEIGHT_RECT=65;
const int SLEEP_WIDTH_RECT=65;

const int ICE_POSX_RECT=205;
const int ICE_POSY_RECT=0;
const int ICE_HEIGHT_RECT=65;
const int ICE_WIDTH_RECT=65;

const int BOOK_POSX_RECT=135;
const int BOOK_POSY_RECT=0;
const int BOOK_HEIGHT_RECT=65;
const int BOOK_WIDTH_RECT=65;

const int ARROWLEFT_POSX_RECT=430;
const int ARROWLEFT_POSY_RECT=12;
const int ARROWLEFT_HEIGHT_RECT=40;
const int ARROWLEFT_WIDTH_RECT=40;

const int ARROWRIGHT_POSX_RECT=380;
const int ARROWRIGHT_POSY_RECT=12;
const int ARROWRIGHT_HEIGHT_RECT=40;
const int ARROWRIGHT_WIDTH_RECT=40;

const int ARROWUP_POSX_RECT=335;
const int ARROWUP_POSY_RECT=12;
const int ARROWUP_HEIGHT_RECT=40;
const int ARROWUP_WIDTH_RECT=40;

const int ARROWDOWN_POSX_RECT=285;
const int ARROWDOWN_POSY_RECT=12;
const int ARROWDOWN_HEIGHT_RECT=40;
const int ARROWDOWN_WIDTH_RECT=40;


/****************** Nom de la fonction **********************
* initElem                                                  *
******************** Auteur , Dates *************************
* VIGNAUD Loic - 03/12/2016                                 *
********************* Description ***************************
* La fonction affecte à chaque élément son rectangle de     *
* lecture.
*********************** Entrées *****************************
* La fonction prend chaque élément (de type Elem) en entrée *
*********************** Sorties *****************************
* Etant une action la fonction ne renvoie rien              *
************************************************************/
void initElem(Element &awake,Element &sleep, Element &ice, Element &book, Element &arrowL, Element &arrowR, Element &arrowU, Element &arrowD)
{
    awake.read_elem.x = AWAKE_POSX_RECT;
    awake.read_elem.y = AWAKE_POSY_RECT;
    awake.read_elem.h = AWAKE_HEIGHT_RECT;
    awake.read_elem.w = AWAKE_WIDTH_RECT;

    sleep.read_elem.x = SLEEP_POSX_RECT;
    sleep.read_elem.y = SLEEP_POSY_RECT;
    sleep.read_elem.h = SLEEP_HEIGHT_RECT;
    sleep.read_elem.w = SLEEP_WIDTH_RECT;

    ice.read_elem.x = ICE_POSX_RECT;
    ice.read_elem.y = ICE_POSY_RECT;
    ice.read_elem.h = ICE_HEIGHT_RECT;
    ice.read_elem.w = ICE_WIDTH_RECT;

    book.read_elem.x = BOOK_POSX_RECT;
    book.read_elem.y = BOOK_POSY_RECT;
    book.read_elem.h = BOOK_HEIGHT_RECT;
    book.read_elem.w = BOOK_WIDTH_RECT;

    arrowL.read_elem.x = ARROWLEFT_POSX_RECT;
    arrowL.read_elem.y = ARROWLEFT_POSY_RECT;
    arrowL.read_elem.h = ARROWLEFT_HEIGHT_RECT;
    arrowL.read_elem.w = ARROWLEFT_WIDTH_RECT;

    arrowR.read_elem.x = ARROWRIGHT_POSX_RECT;
    arrowR.read_elem.y = ARROWRIGHT_POSY_RECT;
    arrowR.read_elem.h = ARROWRIGHT_HEIGHT_RECT;
    arrowR.read_elem.w = ARROWRIGHT_WIDTH_RECT;

    arrowU.read_elem.x = ARROWUP_POSX_RECT;
    arrowU.read_elem.y = ARROWUP_POSY_RECT;
    arrowU.read_elem.h = ARROWUP_HEIGHT_RECT;
    arrowU.read_elem.w = ARROWUP_WIDTH_RECT;

    arrowD.read_elem.x = ARROWDOWN_POSX_RECT;
    arrowD.read_elem.y = ARROWDOWN_POSY_RECT;
    arrowD.read_elem.h = ARROWDOWN_HEIGHT_RECT;
    arrowD.read_elem.w = ARROWDOWN_WIDTH_RECT;

}

/****************** Nom de la fonction **********************
* curseurSurMonstre                                         *
******************** Auteur , Dates *************************
* RUBIO Anthony - 09/12/2016                                *
********************* Description ***************************
* La fonction permet de déterminer si le curseur est        *
* positionné sur un monstre (pour gérer le déplacement)     *
*********************** Entrées *****************************
* La fonction prend en entrée une matrice                   *
*********************** Sorties *****************************
* La fonction renvoie un booléen qui est vraie si le curseur*
* est positionné sur une case contenant une monstre, faux   *
* sinon.                                                    *
************************************************************/
bool cursorOnMonster(Level lvl)
{
    int x, y;
    int i=0;
    int j=0;
    bool find=false;
    SDL_GetMouseState(&x,&y);

    i=(y-decalY)/(coefY); // transformation des coordonnées du curseur en coordonnées de la matrice.
    j=(x-decalX)/(coefX);

    if( i <0 || i >= NB_LINE ||  j <0 || j >= NB_ROW ) return false;

    if(lvl[i][j]==1 ){
        find=true;
    }

    return find;
}

/****************** Nom de la fonction **********************
* deplacementMonstre                                        *
******************** Auteur , Dates *************************
* VIGNAUD Loic - RUBIO Anthony - 09/12/2016                 *
********************* Description ***************************
* Associe le déplacement correspondant à la direction       *
* (prise en paramètre) donnée dans le main afin de déplacer *
* le monstre dans la matrice.                               *
*********************** Entrées *****************************
* La Matrice, un entier pour la direction, un pour chaque   *
* indice, le charactère a nous permettant de stocker le     *
* niveau actuel, la chaine de charactère contenant le       *
* fichier de niveaux, chaqu'un des elements et              *
*  les deux surfaces écran/niveau                           *
*********************** Sorties *****************************
* Retourne rien car c'est une action, si ce n'est la grille *
*  qu'elle modifie par référence                            *
************************************************************/

void monsterMovement(Level &lvl, int directionM, int startLine, int startRow, char a, string map, Element awake, Element sleep, Element ice, Element book, Element arrowL, Element arrowR, Element arrowU, Element arrowD, SDL_Surface *levelSurface, SDL_Surface *screen)
{
    switch(directionM){
    case 0: // Monstre prend le mouvement vers la gauche
        while((lvl[startLine][startRow-1]==0) && (startRow>=0) && startRow >= 0){  // on déplace le monstre dans la matrice jusqu'a ce qu'il rencontre un element.
            lvl[startLine][startRow-1]=1;
            lvl[startLine][startRow]=0;
            startRow--;
        }
        if (startLine<0 || startLine >= NB_LINE-1 || startRow < 0 || startRow >= NB_ROW) // si le monstre sort on reinitialise le niveau.
        {
            file2Level(map,lvl,a);
            drawLevel(lvl,screen, awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface);
        }
        switch (lvl[startLine][startRow-1]) {   // Analyse de la prochaine case
        case 2: //Si elle contient un monstre endormi, il se reveille
            lvl[startLine][startRow-1]=1;
            lvl[startLine][startRow]=1; // On reinitialise le monstre dans la case qui précède pour éviter tout conflit avec les flèches.
            break;
        case 4: //Si elle contient de la glace, elle se casse
            lvl[startLine][startRow-1]=0;
            lvl[startLine][startRow]=1;
            break;
        case 5: //Si elle contient une flèche vers la gauche.
            monsterMovement(lvl,0,startLine,startRow-2,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen); // On réalise un appel récursif de la fonction monsterMovement pour réaliser le déplacement correspondant à la flèche. On donne la valeur à la direction en fonction de la flèche en question (gauche:0, droite:1, haut:2, bas:3)
            lvl[startLine][startRow]=0;
            break;
        case 6: //Si elle contient une flèche vers la droite.
            monsterMovement(lvl,1,startLine,startRow,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;

            break;
        case 7: //Si elle contient une flèche vers le haut.
            monsterMovement(lvl,2,startLine-1,startRow-1,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 8: //Si elle contient une flèche vers le bas.
            monsterMovement(lvl,3,startLine+1,startRow-1,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        default:
            break;
        }
        ;
        break;

    case 1: // Monstre prend le mouvement vers la droite.
        while((lvl[startLine][startRow+1]==0) && (startRow<NB_ROW) && startRow >= 0){
            lvl[startLine][startRow+1]=1;
            lvl[startLine][startRow]=0;
            startRow++;
        }
        if (startLine<0 || startLine >= NB_LINE-1 || startRow < 0 || startRow >= NB_ROW)
        {
            file2Level(map,lvl,a);
            drawLevel(lvl,screen, awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface);
        }
        switch (lvl[startLine][startRow+1]) {
        case 2:
            lvl[startLine][startRow+1]=1;
            lvl[startLine][startRow]=1;
            break;
        case 4:
            lvl[startLine][startRow+1]=0;
            lvl[startLine][startRow]=1;
            break;
        case 5:
            monsterMovement(lvl,0,startLine,startRow,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 6:
            monsterMovement(lvl,1,startLine,startRow+2,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 7:
            monsterMovement(lvl,2,startLine-1,startRow+1,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 8:
            monsterMovement(lvl,3,startLine+1,startRow+1,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        default:
            break;
        }
        ;
        break;

    case 2: // Monstre prend le mouvement vers le haut.
        while((lvl[startLine-1][startRow]==0) && (startLine>=0) && startLine>=0 ){
            lvl[startLine-1][startRow]=1;
            lvl[startLine][startRow]=0;
            startLine--;
        }
        if (startLine<0 || startLine >= NB_LINE-1 || startRow < 0 || startRow >= NB_ROW)
        {
            file2Level(map,lvl,a);
            drawLevel(lvl,screen, awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface);
        }
        switch (lvl[startLine-1][startRow]) {
        case 2:
            lvl[startLine-1][startRow]=1;
            lvl[startLine][startRow]=1;
            break;
        case 4:
            lvl[startLine-1][startRow]=0;
            lvl[startLine][startRow]=1;
            break;
        case 5:
            monsterMovement(lvl,0,startLine+1,startRow-1,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 6:
            monsterMovement(lvl,1,startLine+1,startRow+1,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 7:
            monsterMovement(lvl,2,startLine-2,startRow,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 8:
            monsterMovement(lvl,3,startLine,startRow,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        default:
            break;
        }
        ;
        break;

    case 3: // Monstre prend le mouvement vers le bas.
        while((lvl[startLine+1][startRow]==0) && (startLine<NB_LINE && startLine>=0)){
            lvl[startLine+1][startRow]=1;
            lvl[startLine][startRow]=0;
            startLine++;
        }
        if (startLine<0 || startLine >= NB_LINE -1 || startRow < 0 || startRow >= NB_ROW)
        {
            file2Level(map,lvl,a);
            drawLevel(lvl,screen, awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface);
        }
        switch (lvl[startLine+1][startRow]) {
        case 2:
            lvl[startLine+1][startRow]=1;
            lvl[startLine][startRow]=1;
            break;
        case 4:
            lvl[startLine+1][startRow]=0;
            lvl[startLine][startRow]=1;
            break;
        case 5:
            monsterMovement(lvl,0,startLine+1,startRow-1,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 6:
            monsterMovement(lvl,1,startLine+1,startRow+1,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 7:
            monsterMovement(lvl,2,startLine,startRow,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        case 8:
            monsterMovement(lvl,3,startLine+2,startRow,a,map,awake,sleep,ice,book,arrowL,arrowR,arrowU,arrowD,levelSurface,screen);
            lvl[startLine][startRow]=0;
            break;
        default:
            break;
        }
        ;
        break;
    }


}
