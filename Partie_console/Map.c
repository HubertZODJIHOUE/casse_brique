#include "Map.h"
#include <string.h>

carte_info load_map(const char* name) {
    int r;
    char p[1024];

    char buffer[10];
    int cpt = 0;

    int cptLigne = 0;
    carte_info info;

    int fd = open(name, O_RDONLY);

    if(fd == -1) {
        perror(name);
        exit(-1);
    }

    while((r=read(fd,p,1))>0 && p[0] != ' ') {
        buffer[cpt] = p[0];
        cpt++;
    }
    buffer[cpt] = '\0';
    cpt = 0;

    info.h = atoi(buffer);


    while((r=read(fd,p,1))>0 && p[0] != '\n') {
        buffer[cpt] = p[0];
        cpt++;
    }
    buffer[cpt] = '\0';
    info.l = atoi(buffer);

    info.carte = (char**) calloc(sizeof(char*),info.h);
    for(int i = 0; i < info.h; i ++) {
        info.carte[i] =  calloc(1,info.l+1);
    }

    while((r=read(fd,p,info.l+1))>0 && cptLigne < info.h) {
        strcpy(info.carte[cptLigne],p);
        cptLigne++;
    }

    cptLigne = 0;


    lseek(fd,-(info.l+1),SEEK_CUR);
    

    info.bonus = (char**) calloc(sizeof(char*),info.h);
    for(int i = 0; i < info.h; i ++) {
        info.bonus[i] =  calloc(1,info.l+1);
    }


    while((r=read(fd,p,info.l+1))>0 && cptLigne < info.h) {
        strcpy(info.bonus[cptLigne],p);
        cptLigne++;
    }
    return info;
}


void display_map(char** tab,int h,int l) {
    for(int i = 0; i < h; i ++) {
        for(int j = 0; j < l; j ++) {
            if(tab[i][j] == '@' || tab[i][j] == '*' || tab[i][j] == '+') {
                printf(RED "%c" RESET,tab[i][j]);
            } else {
                printf("%c",tab[i][j]);
            }
        }
        printf("\n");
    }
}