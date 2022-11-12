
#ifndef _LIST_H
#define _LIST_H
#include "projet.h"
#include <stdbool.h>

/**
 * @brief 
 * 
 * @return list 
 */
extern list listvide ();

/**
 * @brief 
 * 
 * @param l 
 * @param i 
 * @param j 
 * @param t 
 * @return list 
 */
extern list ajout_debut (list l, int i, int j, time_t t);

/**
 * @brief 
 * 
 * @param l 
 * @return list 
 */
extern list supprime_fin (list l);

/**
 * @brief 
 * 
 * @param l 
 * @param i 
 * @param j 
 * @return true 
 * @return false 
 */
extern bool check(list l, int i, int j);

/**
 * @brief 
 * 
 * @param l 
 * @return int 
 */
extern int length (list l);

/**
 * @brief 
 * 
 * @param l 
 */
extern void affiche(list l);

#endif