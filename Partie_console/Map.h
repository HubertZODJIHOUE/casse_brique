#ifndef _MAP_H
#define _MAP_H
#include "projet.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief 
 * 
 * @param name 
 * @return carte_info 
 */
extern carte_info load_map(const char* name);

/**
 * @brief 
 * 
 * @param tab 
 * @param h 
 * @param l 
 */
extern void display_map(char** tab,int h,int l);

#endif