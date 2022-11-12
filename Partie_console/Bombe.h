
#ifndef _BOMBE_H
#define _BOMBE_H

#include <stdbool.h>
#include "projet.h"

/**
 * une foction qui a comme rôle d'exploser une bombe
 * 
 * @param i 
 * @param j 
 * @param clone 
 * @param x 
 * @param y 
 * @return int 
 */
extern int explose(int i,int j,carte_info clone, player* x, player* y);

/**
 * une fonction qui a comme rôle de vérifier si le temps est arrivé pour exploser la première bombe de la liste des bombes qui sont attentes d'explosion
 * 
 * @param etat 
 * @param clone 
 * @param portee 
 * @param x 
 * @param y 
 * @param boom 
 * @return list 
 */
extern list time_to_explose(list etat, carte_info clone, int portee, player* x, player* y,bool* boom);

#endif