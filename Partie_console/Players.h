
#ifndef _PLAYERS_H
#define _PLAYERS_H
#include <stdbool.h>

/**
 * une fonction qui a comme rôle de déplacer le player et renvoi un 0 si le player peut se déplacer sinon elle renvoie un -1
 * 
 * @param i 
 * @param j 
 * @param i_change 
 * @param j_change 
 * @param y 
 * @param clone 
 * @param etat_x 
 * @param etat_y 
 * @return int 
 */
extern int move_player (int i,int j,int i_change,int j_change, player* y, carte_info clone, list etat_x, list etat_y);

/**
 * une fonction qui a comme rôle de change la valeur des paramètres i et j par la position de player dans la map 
 * 
 * @param clone 
 * @param x 
 * @param i 
 * @param j 
 */
extern void place(carte_info clone, player x, int* i, int* j);

#endif