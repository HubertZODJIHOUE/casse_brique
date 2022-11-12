#include "file.h"
#include "projet.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

char* display_mod() {
    printf("\e[1;1H\e[2J");
    DIR* d = opendir("mods");
    struct dirent* dirp;

    write(1,"Casse brique\n",11); 
    write(1,"Tapez nom de mode pour chosir, q pour quitter\n",47);
    while((dirp = readdir(d)) != NULL) {
            if(strcmp(dirp->d_name,".") != 0 && strcmp(dirp->d_name,"..") != 0) {
                write(1,"> ",2);
                write(1,dirp->d_name,strlen(dirp->d_name));
                write(1,"\n",1);
            }
    }
    closedir(d);
    return load_mod();
}


char* concat(const char* s1, const char* s2) {
    char* result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result,s1);
    strcat(result,s2);
    return result;
}


char* load_mod() {
    char mod[1024];
    printf("Mod?: ");
    fgets(mod,1024,stdin);


    mod[strlen(mod)-1] = '\0';

    if(strcmp(mod,"q") == 0) exit(1);

    DIR* d = opendir(concat("mods/",mod));
    if(d) return display_level(concat("mods/",mod));
    else return display_mod();
}



char* display_level(const char* lien) {
    printf("\e[1;1H\e[2J");
    printf("lien: %s\n",lien);
    int r;
    char buffer[1024];

    int fd = open(concat(lien,"/deroulement.txt"),O_RDONLY);

    if(fd == -1) {
        perror("deroulement.txt");
        exit(-1);
    }

    while((r=read(fd,buffer,1024)) > 0) {
        write(1,buffer,r);
    }
    close(fd);
    return load_level(lien);
}


char* load_level(const char* lien) {
    char niveau[1024];
    printf("Niveau? :");
    fgets(niveau,1024,stdin);


    niveau[strlen(niveau)-1] = '\0';

    if(strcmp(niveau,"p") == 0) return display_mod();

    char* s = concat(lien,concat("/niveaux/",concat(niveau,".txt")));
    int fd = open(s,O_RDONLY);
    if(fd == -1) return display_level(lien);
    return s;
}
