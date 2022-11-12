#ifndef _FILE_H
#define _FILE_H

/**
 * une fonction qui a comme rôle d'afficher le mode de jeux
 * 
 * @return char* 
 */
extern char* display_mod();

/**
 * une fonction qui a comme rôle de concaténer deux chaînes de caractères.
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
extern char* concat(const char* s1, const char* s2);

/**
 * une fonction qui a comme rôle de charger le mode jeux à partir des fichiers .txt
 * 
 * @return char* 
 */
extern char* load_mod();

/**
 * une fonction qui a comme rôle d'afficher les niveaux disponibles dans un mode de jeux choisi par l'utilisateur
 * 
 * @param lien 
 * @return char* 
 */
extern char* display_level(const char* lien);

/**
 * une fonction qui a comme rôle de charger le niveau de jeux à partir des fichiers .txt
 * 
 * @param lien 
 * @return char* 
 */
extern char* load_level(const char* lien);

#endif