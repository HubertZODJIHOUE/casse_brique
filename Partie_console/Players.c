#include "projet.h"
#include "Players.h"
#include "Map.h"

void switch_player (carte_info clone, player* x, int i ,int j) {
    if ((j == 0 || j == clone.l-1) && clone.carte[i][j] == x->signe) {
        if (j == 0) {
            clone.carte[i][clone.l-1] = clone.carte[i][j];
            clone.carte[i][j] = ' ';
        } 

        if (j == clone.l-1) {
            clone.carte[i][0] = clone.carte[i][j];
            clone.carte[i][j] = ' ';
        }

       display_map(clone.carte,clone.h,clone.l);
    } else if ((i == 0 || i == clone.h-1) && (clone.carte[i][j] == x->signe)) {
        if (i == 0) {
            clone.carte[i][clone.h-1] = clone.carte[i][j];
            clone.carte[i][j] = ' ';
        } 

        if (i == clone.h-1) {
            clone.carte[i][0] = clone.carte[i][j];
            clone.carte[i][j] = ' ';
        }

       display_map(clone.carte,clone.h,clone.l);
    }
}


int move_player (int i,int j,int i_change,int j_change, player* y, carte_info clone, list etat_x, list etat_y) {
    if (clone.carte[i_change][j_change] == ' ' || clone.carte[i_change][j_change] == '+' || clone.carte[i_change][j_change] == '*' || (clone.carte[i_change][j_change] == '@' && (check(etat_x,i_change,j_change) == 0) && (check(etat_y,i_change,j_change) == 0))) {

        if(clone.carte[i_change][j_change] == '+') y->boom.vitesse ++;
        if(clone.carte[i_change][j_change] == '@') y->boom.pose ++;
        if(clone.carte[i_change][j_change] == '*') y->boom.portee ++;

        clone.carte[i_change][j_change] = y->signe;

        if (clone.carte[i][j] != '@') clone.carte[i][j] = ' ';

        switch_player (clone, y, i_change ,j_change);

    } else {
        return -1;
    }
    return 0;
}


void place(carte_info clone, player x, int* i, int* j) {
    for(int a = 0; a < clone.h; a ++) {
        for(int b = 0; b < clone.l; b ++) {
            if (clone.carte[a][b] == x.signe) {
                *i = a; *j = b;
            }
        }
    }
}