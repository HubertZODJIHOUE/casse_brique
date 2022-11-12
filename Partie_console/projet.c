#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdbool.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>
#include "projet.h"
#include "Bombe.h"
#include "Players.h"
#include "List.h"
#include "file.h"
#include "Map.h"


carte_info carte_clone(carte_info info) {
    carte_info clone;
    clone.h = info.h;
    clone.l = info.l;

    clone.carte = (char**) malloc(sizeof(char*)*clone.h);
    for(int i = 0; i < clone.h; i ++) {
        clone.carte[i] =  malloc(clone.l+1);
        strcpy(clone.carte[i],info.carte[i]);
    }

    clone.bonus = (char**) malloc(sizeof(char*)*clone.h);
    for(int i = 0; i < clone.h; i ++) {
        clone.bonus[i] =  malloc(clone.l+1);
        strcpy(clone.bonus[i],info.bonus[i]);
    }

    return clone;
}


void display_info_of_player (player x, player y, carte_info clone) {
    //printf("\e[1;1H\e[2J");
    printf("%s - vie: %d - vitesse: %d - portee: %d - pose %d.\n",x.nom,x.vie,x.boom.vitesse,x.boom.portee,x.boom.pose);
    printf("%s - vie: %d - vitesse: %d - portee: %d - pose %d.\n",y.nom,y.vie,y.boom.vitesse,y.boom.portee,y.boom.pose);
    display_map(clone.carte,clone.h,clone.l);
}


int start_game (const char* name, player x, player y) {
    int ix = 0; int jx = 0; int iy = 0; int jy = 0;    
    list etat_x = listvide(); list etat_y = listvide();
    bool boomx = 0; 
    bool boomy = 0;
    time_t t;
    carte_info clone = carte_clone(load_map(name));
    display_info_of_player(x,y,clone);

    do {
        place(clone,y,&iy,&jy);
        place(clone,x,&ix,&jx);

        char c[10];
        scanf( "%s", c );

        //déplacer x et y
        switch(c[0]) {

            //en haut
            case 'A':
            move_player(iy,jy,iy-y.boom.vitesse,jy,&y,clone,etat_x,etat_y);
            break;

            //à gauche
            case 'D':
            move_player(iy,jy,iy,jy-y.boom.vitesse,&y,clone,etat_x,etat_y);
            break;

            //en bas
            case 'B':
            move_player(iy,jy,iy+y.boom.vitesse,jy,&y,clone,etat_x,etat_y);
            break;

            //à droite
            case 'C':
            move_player(iy,jy,iy,jy+y.boom.vitesse,&y,clone,etat_x,etat_y);
            break;

            //en haut
            case 'z':
            move_player(ix,jx,ix-x.boom.vitesse,jx,&x,clone,etat_x,etat_y);
            break;

            //à gauche
            case 'q':
            move_player(ix,jx,ix,jx-x.boom.vitesse,&x,clone,etat_x,etat_y);
            break;

            //en bas
            case 's':
            move_player(ix,jx,ix+x.boom.vitesse,jx,&x,clone,etat_x,etat_y);
            break;

            //à droite
            case 'd':
            move_player(ix,jx,ix,jx+x.boom.vitesse,&x,clone,etat_x,etat_y);
            break;

            //les autres cas
            default:
            break; 
        }


        if(length(etat_x) != 0) {
            etat_x = time_to_explose(etat_x,clone,x.boom.portee,&x,&y,&boomx);
        }

        if(length(etat_y) != 0) {
            etat_y = time_to_explose(etat_y,clone,y.boom.portee,&y,&x,&boomy);
        }

        if(c[0] == 'w' && length(etat_x) < x.boom.pose) {
            clone.carte[ix][jx] = '@'; 
            if(check(etat_x,ix,jx) == false) etat_x = ajout_debut(etat_x,ix,jx,time(&t));
        }

        if(c[0] == '\n' && length(etat_y) < y.boom.pose) {
            clone.carte[iy][jy] = '@'; 
            if(check(etat_y,iy,jy) == false) etat_y = ajout_debut(etat_y,iy,jy,time(&t));
        }


        if(c != 0 || boomx != 0 || boomy != 0) {
            display_info_of_player(x,y,clone);
            if(boomx != 0) boomx = 0;
            if(boomy != 0) boomy = 0;
        }

        if(x.vie <= 0) {
            printf("%s gagné.\n",y.nom);
            exit(-1);
        }

        if(y.vie <= 0) {
            printf("%s gagné.\n",x.nom);
            exit(-1);
        }

    } while(1);
    return 0;
}

player initialise(char* name, char signe) {
    bombe bx;
    bx.vitesse = 1;
    bx.portee = 1;
    bx.pose = 1;
    player x;
    x.vie = 3;
    x.boom = bx;
    x.nom = name;
    x.signe = signe;

    return x;
}


int main(int argc, char** argv) {

 player x = initialise("Joueur 1", 'x');
 player y = initialise("Joueur 2", 'y');

 start_game(display_mod(),x,y);

 return 0;
}
















