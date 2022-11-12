#include "Bombe.h"
#include "projet.h"
#include "Players.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

int explose(int i,int j,carte_info clone, player* x, player* y) {

    if(clone.carte[i][j] != '0') {
        if(clone.carte[i][j] != ' ' && clone.carte[i][j] != '+' && clone.carte[i][j] != '*' && clone.carte[i][j] != '@' && clone.carte[i][j] != 'x' && clone.carte[i][j] != 'y') {
            if(clone.carte[i][j] != '1') {
                clone.carte[i][j] = clone.carte[i][j] - 1;
            } else { 
                clone.carte[i][j] = clone.bonus[i][j];
            }
        } else {
            if(clone.carte[i][j] == 'x') {
                    x->vie --;
            }

            if(clone.carte[i][j] == 'y') {
                    y->vie --;
            }
        }
    } else {
        return -1;
    } 
    return 0;
}


list time_to_explose(list etat, carte_info clone, int portee, player* x, player* y,bool* boom) {
    time_t t;

    block* p = NULL;
    block* c = etat;
    while (c != NULL) {
        p = c;
        c = c->next;
    }

    time(&t);
    double total_t = difftime(t,p->t);
    printf("time %f\n",total_t);
    if(total_t >= 60) {
        printf("Bommmmmmmmm!\n");
        int i = 0; int j = 0;
        place(clone,*x,&i,&j);
        if(i == 0 && j == 0 && p == etat) {
            clone.carte[p->i][p->j] = x->signe;
            x->vie--;
        } else {
            clone.carte[p->i][p->j] = ' ';
        }

        for(int a = 1; a <= portee; a++) {
            if(explose(p->i,p->j+a,clone,x,y) == -1) a = portee + 1;
        }

        for(int a = 1; a <= portee; a++) {
            if(explose(p->i,p->j-a,clone,x,y) == -1) a = portee + 1;
        }

        for(int a = 1; a <= portee; a++) {
            if(explose(p->i+a,p->j,clone,x,y) == -1) a = portee + 1;
        }

        for(int a = 1; a <= portee; a++) {
            if(explose(p->i-a,p->j,clone,x,y) == -1) a = portee + 1;
        }

        etat = supprime_fin(etat);
        *boom = 1;
    }

    return etat;
}