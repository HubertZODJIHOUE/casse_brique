
#ifndef _PROJET_H
#define _PROJET_H
#include <time.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"


typedef struct Carte_info carte_info;
typedef struct Bombe bombe;
typedef struct Player player;


/**
 * la structure qui présente la map de jeux
 * 
 */
struct Carte_info {
    char** carte; 
    int h; 
    int l; 
    char** bonus;
};


/**
 * la structure qui présente la bombe
 * 
 */
struct Bombe {
    int vitesse; 
    int portee; 
    int pose; 
};

/**
 * la structure qui présente le player
 * 
 */
struct Player {
    char signe; 
    int vie;
    char* nom;
    bombe boom;
};

typedef struct block_s block;
typedef block* list;

/**
 * la structure qui présente la liste
 * 
 */
struct block_s{
    int i;
    int j;
    time_t t;
    block* next;
};

/**
 * une fonction qui supprime le dernier élément dans une liste
 * 
 * @param l 
 * @return list 
 */
extern list supprime_fin (list l);

/**
 * une fonction qui initialise les informations d'un player
 * 
 * @param name 
 * @param signe 
 * @return player 
 */
extern player initialise(char* name, char signe);

#endif
