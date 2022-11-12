#include "List.h"
#include <stdlib.h>
#include <stdio.h>

list listvide () {
    list l = NULL;
    return l;
}

list ajout_debut (list l, int i, int j, time_t t){
    block* n = (block*) malloc(sizeof(block));
    n->i = i;
    n->j = j;
    n->t = t; 
    n->next = l;
    l = n;
    return l;
}

list supprime_fin (list l) {
    block* b = NULL;
    block* p = NULL;
    block* c = l;

    while (c != NULL) {
        b = p;
        p = c;
        c = c->next;
    }

    if(b != NULL) b->next = NULL;
    else l = listvide();

    return l;
}

bool check(list l, int i, int j) {
    block* c = l;

    while (c != NULL) {
        if (c->i == i && c-> j == j) return 1;
        c = c->next;
    }

    return 0;
}

int length (list l) {
    int p = 0;
    block* t = l;
    while( t != NULL) {
        p++;
        t = t->next;
    }
    return p;
}

void affiche(list l){
    block* b = l;
    while(b != NULL ){
        printf("(%d,%d,%lld) ", b->i, b->j,b->t);
        b = b->next;
    }
}