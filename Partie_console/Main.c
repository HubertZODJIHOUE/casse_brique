#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

#include "Map.h"
#include "List.h"
#include "Players.h"

// gcc List.o Map.o -I src/include -L src/lib -o Main Main.c -lmingw32 -lSDL2main -lSDL2

//gcc List.o Bombe.o file.o Map.o Players.o projet.c

const int WIDTH = 950, HEIGHT = 600;

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius, int cpp)
{
    x = 18 + 21 * x;
    y = 204 + 22 * y;
    if (cpp == 0) {
        SDL_SetRenderDrawColor(renderer, 255, 255 , 0 , 255);
    }
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h; 
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}


void file_bomb (carte_info *map ,int *index_x , int *index_y) {
    if ((*index_x >= 2 && *index_x <= map->h-3) && (*index_y >= 2 && *index_y <= map->l-3) ) {
        if ((map->carte[*index_x][*index_y+2] == '0' &&  map->carte[*index_x][*index_y+1] == ' ') || (map->carte[*index_x][*index_y+2] == '1' && map->carte[*index_x][*index_y+1] == ' ')) {
            map->carte[*index_x][*index_y+1] = '@';
        } else if ((map->carte[*index_x][*index_y-2] == '0' && map->carte[*index_x][*index_y-1] == ' ') || (map->carte[*index_x][*index_y-2] == '1' && map->carte[*index_x][*index_y-1] == ' ')) {
            map->carte[*index_x][*index_y-1] = '@';
        } else if ((map->carte[*index_x+2][*index_y] == '0' && map->carte[*index_x+1][*index_y] == ' ') || (map->carte[*index_x+2][*index_y] == '1' && map->carte[*index_x+1][*index_y] == ' ')) {
            map->carte[*index_x+1][*index_y] = '@';
        } else if ((map->carte[*index_x-2][*index_y] == '0' && map->carte[*index_x-1][*index_y] == ' ') || (map->carte[*index_x-2][*index_y] == '1' && map->carte[*index_x-1][*index_y] == ' ')) {
            map->carte[*index_x-1][*index_y] = '@';
        }
    } else if (*index_x == 1 || *index_x == map->h-2) {
        if (map->carte[*index_x][*index_y+1] == ' ') {
            map->carte[*index_x][*index_y+1] = '@';
        } else if (map->carte[*index_x][*index_y-1] == ' ') {
            map->carte[*index_x][*index_y-1] = '@';
        }
    }  else if (*index_y == map->l-2 || *index_y == 1) {
        if (map->carte[*index_x+1][*index_y] == ' ') {
            map->carte[*index_x+1][*index_y] = '@';
        } else if (map->carte[*index_x-1][*index_y] == ' ') {
            map->carte[*index_x-1][*index_y] = '@';
        }
    } 
}

void draw_bomb (SDL_Renderer *renderer, int index_x , int index_y) {
    draw_circle(renderer, index_x, index_y, 5 ,0);
}

void diplay_info_of_playerc (SDL_Renderer *renderer) {
} 

void draw_player (SDL_Renderer *renderer, int index_x , int index_y) {
    SDL_Rect rect;
    // SDL_RenderClear(renderer);
    rect.x = 15 + 21 * index_x;
    rect.y = 205+ 21 * index_y;
    rect.w = 10;
    rect.h = 10;
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}

void draw_wall (SDL_Renderer *renderer, int index_x , int index_y , int cpp) {
        SDL_Rect rect;
        rect.x = 10 + 21 * index_x;
        rect.y = 200 + 21 * index_y;
        rect.w = 20;
        rect.h = 20;

        if (cpp == 0) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
        } else if (cpp == 1) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        } else if  (cpp == 3) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        } else if (cpp == 4) {
            SDL_SetRenderDrawColor(renderer, 139, 0, 0, 0);
        } else if (cpp == 5) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        } else if (cpp == 6) {
            SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
        }
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
}

void move_players (SDL_Renderer *renderer,carte_info map, int *pos_x , int *pos_y, char dir) {
    printf("pos_x : %d  pos_y : %d\n",*pos_x,*pos_y);
    draw_wall (renderer, *pos_y , *pos_x , 3);
    switch (dir)
    {
    case 'Z':
        if (map.carte[*pos_x-1][*pos_y] != '0' && map.carte[*pos_x-1][*pos_y] != '1' && map.carte[*pos_x-1][*pos_y] != '2' && map.carte[*pos_x-1][*pos_y] != '3' && map.carte[*pos_x-1][*pos_y] != '4' && map.carte[*pos_x-1][*pos_y] != '5' && map.carte[*pos_x-1][*pos_y] != '6' && map.carte[*pos_x-1][*pos_y] != '7' && map.carte[*pos_x-1][*pos_y] != '8' && map.carte[*pos_x-1][*pos_y] != '9' && map.carte[*pos_x-1][*pos_y] != '@') {
            map.carte[*pos_x][*pos_y] = ' ';
            *pos_x = *pos_x-1;
            map.carte[*pos_x][*pos_y] = 'y';
            break;
        } else {
            break;
        }
    case 'S':
        if (map.carte[*pos_x+1][*pos_y] != '0' && map.carte[*pos_x+1][*pos_y] != '1' && map.carte[*pos_x+1][*pos_y] != '2' && map.carte[*pos_x+1][*pos_y] != '3' && map.carte[*pos_x+1][*pos_y] != '4' && map.carte[*pos_x+1][*pos_y] != '5' && map.carte[*pos_x+1][*pos_y] != '6' && map.carte[*pos_x+1][*pos_y] != '7' && map.carte[*pos_x+1][*pos_y] != '8' && map.carte[*pos_x+1][*pos_y] != '9' && map.carte[*pos_x+1][*pos_y] != '@') {
            map.carte[*pos_x][*pos_y] = ' ';
            *pos_x = *pos_x+1;
            map.carte[*pos_x][*pos_y] = 'y';
            break;
        } else {
            break;
        }
    case 'D':
        if (map.carte[*pos_x][*pos_y+1] != '0' && map.carte[*pos_x][*pos_y+1] != '1' && map.carte[*pos_x][*pos_y+1] != '2' && map.carte[*pos_x][*pos_y+1] != '3' && map.carte[*pos_x][*pos_y+1] != '4' && map.carte[*pos_x][*pos_y+1] != '5' && map.carte[*pos_x][*pos_y+1] != '6' && map.carte[*pos_x][*pos_y+1] != '7' && map.carte[*pos_x][*pos_y+1] != '8' && map.carte[*pos_x][*pos_y+1] != '9' && map.carte[*pos_x][*pos_y+1] != '@') {
            if (*pos_y < 42) {
                map.carte[*pos_x][*pos_y] = ' ';
                *pos_y = *pos_y+1;
                map.carte[*pos_x][*pos_y] = 'y';
                break;
            } else {
                if (*pos_y == 42) {
                    map.carte[*pos_x][*pos_y] = ' ';
                    *pos_y = 0;
                    map.carte[*pos_x][*pos_y] = 'y';
                    break;
                }
            }
        } else {
            break;
        }
    case 'Q':
        if (map.carte[*pos_x][*pos_y-1] != '0' && map.carte[*pos_x][*pos_y-1] != '1' && map.carte[*pos_x][*pos_y-1] != '2' && map.carte[*pos_x][*pos_y-1] != '3' && map.carte[*pos_x][*pos_y-1] != '4' && map.carte[*pos_x][*pos_y-1] != '5' && map.carte[*pos_x][*pos_y-1] != '6' && map.carte[*pos_x][*pos_y-1] != '7' && map.carte[*pos_x][*pos_y-1] != '8' && map.carte[*pos_x][*pos_y-1] != '9' && map.carte[*pos_x][*pos_y-1] != '@') {
            if (*pos_y > 1) {
                map.carte[*pos_x][*pos_y] = ' ';
                *pos_y = *pos_y-1;
                map.carte[*pos_x][*pos_y] = 'y';
                break;
            } else {
                if (*pos_y == 1) {
                    map.carte[*pos_x][*pos_y] = ' ';
                    *pos_y = 43;
                    map.carte[*pos_x][*pos_y] = 'y';
                    break;
                }
            }
        } else {
            break;
        }
    default:
        break;
    }
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


int explose(int i,int j,carte_info *clone, player* x, player* y) {

    if(clone->carte[i][j] != '0') {
        if(clone->carte[i][j] != ' ' && clone->carte[i][j] != '+' && clone->carte[i][j] != '*' && clone->carte[i][j] != '@' && clone->carte[i][j] != 'x' && clone->carte[i][j] != 'y') {
            if(clone->carte[i][j] != '1') {
                clone->carte[i][j] = clone->carte[i][j] - 1;
            } else { 
                clone->carte[i][j] = clone->bonus[i][j];
            }
        } else {
            if(clone->carte[i][j] == 'x') {
                if(x->signe == 'x') {
                    x->vie --;
                } else {
                    y->vie --;
                }
            }
            if(clone->carte[i][j] == 'y') {
                if(x->signe == 'y') x->vie --;
                else y->vie --;
            }
        }
    } else {
        return -1;
    } 
    return 0;
}


list time_to_explose(SDL_Renderer *renderer, list etat, carte_info *clone, int portee, player* x, player* y,bool* boom) {
    time_t t;

    block* p = NULL;
    block* c = etat;
    while (c != NULL) {
        p = c;
        c = c->next;
    int index_i ;
    int index_j ;
    if (clone->carte[p->i+1][p->j] == '@') {
        index_i = p->i+1;
        index_j = p->j;
    } else if (clone->carte[p->i-1][p->j] == '@') {
        index_i = p->i-1;
        index_j = p->j;
    } else if (clone->carte[p->i][p->j+1] == '@') {
        index_i = p->i;
        index_j = p->j+1;
    } else if (clone->carte[p->i][p->j-1] == '@') {
        index_i = p->i;
        index_j = p->j-1;
    }

    time(&t);
    double total_t = difftime(t,p->t);
    printf("total_t %f\n",total_t);
    if(total_t >= 50) {
        printf("Bommmmmmmmm!\n");
                printf("i : %d  j : %d\n",index_i,index_j);
                printf("%c\n",clone->carte[index_i][index_j]);
                clone->carte[index_i][index_j] = ' ';
                draw_wall (renderer, index_j , index_i , 3);
                if ((clone->carte[index_i][index_j-1] == '1' || clone->carte[index_i][index_j-1] == ' ') && (index_j-1) != 0 && (index_j-1) != clone->l ) {
                    if (clone->bonus[index_i][index_j-1] == ' ') {
                        clone->carte[index_i][index_j-1] = ' ';
                        draw_wall (renderer, index_j-1 , index_i , 3);
                    } else if (clone->bonus[index_i][index_j-1] == '@') {
                        clone->carte[index_i][index_j-1] = ' ';
                        draw_wall(renderer, index_j-1 , index_i , 4);
                    } else if (clone->bonus[index_i][index_j-1] == '*') {
                        clone->carte[index_i][index_j-1] = ' ';
                        draw_wall(renderer, index_j-1 , index_i , 5);
                    } else if (clone->bonus[index_i][index_j-1] == '+') {
                        clone->carte[index_i][index_j-1] = ' ';
                        draw_wall(renderer, index_j-1 , index_i , 6);
                    }
                }
                if ((clone->carte[index_i][index_j+1] == '1' || clone->carte[index_i][index_j+1] == ' ') && (index_j+1) != 0 && (index_j+1) != clone->l ) {
                    if (clone->bonus[index_i][index_j+1] == ' ') {    
                        clone->carte[index_i][index_j+1] = ' ';
                        draw_wall (renderer, index_j+1 , index_i , 3);
                    } else if (clone->bonus[index_i][index_j-1] == '@') {
                        clone->carte[index_i][index_j+1] = ' ';
                        draw_wall (renderer, index_j+1 , index_i , 4);
                    }  else if (clone->bonus[index_i][index_j-1] == '*') {
                        clone->carte[index_i][index_j+1] = ' ';
                        draw_wall (renderer, index_j+1 , index_i , 5);
                    }  else if (clone->bonus[index_i][index_j-1] == '+') {
                        clone->carte[index_i][index_j+1] = ' ';
                        draw_wall (renderer, index_j+1 , index_i , 6);
                    }
                }
                if ((clone->carte[index_i-1][index_j] == '1' || clone->carte[index_i-1][index_j] == ' ') && (index_i-1) != 0 && (index_i-1) != clone->h ) {
                    if (clone->bonus[index_i-1][index_j] == ' ') {    
                        clone->carte[index_i-1][index_j] = ' ';
                        draw_wall (renderer, index_j , index_i-1 , 3);
                    } else if (clone->bonus[index_i-1][index_j] == '@'){
                        clone->carte[index_i-1][index_j] = ' ';
                        draw_wall (renderer, index_j , index_i-1 , 4);
                    } else if (clone->bonus[index_i-1][index_j] == '*'){
                        clone->carte[index_i-1][index_j] = ' ';
                        draw_wall (renderer, index_j , index_i-1 , 5);
                    } else if (clone->bonus[index_i-1][index_j] == '+'){
                        clone->carte[index_i-1][index_j] = ' ';
                        draw_wall (renderer, index_j , index_i-1 , 6);
                    } 
                }
                if ((clone->carte[index_i+1][index_j] == '1' || clone->carte[index_i+1][index_j] == ' ') && (index_i+1) != 0 && (index_i+1) != clone->h ) {
                    if (clone->bonus[index_i+1][index_j] == ' ') {     
                        clone->carte[index_i+1][index_j] = ' ';
                        draw_wall (renderer, index_j , index_i+1 , 3);
                    } else if (clone->bonus[index_i+1][index_j] == '@') {
                        clone->carte[index_i+1][index_j] = ' ';
                        draw_wall (renderer, index_j , index_i+1 , 4);
                    } else if (clone->bonus[index_i+1][index_j] == '*') {
                        clone->carte[index_i+1][index_j] = ' ';
                        draw_wall (renderer, index_j , index_i+1 , 5);
                    } else if (clone->bonus[index_i+1][index_j] == '+') {
                        clone->carte[index_i+1][index_j] = ' ';
                        draw_wall (renderer, index_j , index_i+1 , 6);
                    } 
                }
        etat = supprime_fin(etat);
        *boom = 1;
    }
    }

    return etat;
}
 

int main( int argc, char *argv[])
{
    // SDL_Init( SDL_INIT_EVERYTHING );
    player x = initialise("Joueur 1", 'x');
    player y = initialise("Joueur 2", 'y');
    time_t t;
    list etat_y = listvide();
    carte_info map = load_map("mods/facile/niveaux/1.txt");
    int pos_x = map.h-2;
    int pos_y = map.l-2;
    bool boomx = 0; 
    bool boomy = 0;
    SDL_Window *window = SDL_CreateWindow( "Bomberman Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
     
    // SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION, 
    //           "Hello World",
    //           "You have successfully compiled and linked an SDL2"
    //           " program, congratulations.", NULL );

    for (int i = 0 ; i < map.h ; i++) {
        for (int j = 0 ; j < map.l ; j++) {
            printf("%c",map.bonus[i][j]);
        }
        printf("\n");
    }
    int continuer = 1;
    while (continuer) 
    {
    if(length(etat_y) != 0) {
            etat_y = time_to_explose(renderer,etat_y,&map,y.boom.portee,&x,&y,&boomy);
    }
    int cpp = 0;
    for (int j = 0 ; j < map.h ; j++) {
        for (int i = 0 ; i < map.l ; i++){ 
            if (map.carte[j][i] != ' ' && map.carte[j][i] != '1' && map.carte[j][i] != 'x' && map.carte[j][i] != 'y' && map.carte[j][i] != '@') {
                cpp = 0;
                draw_wall (renderer , i, j, cpp);
                SDL_RenderPresent(renderer);
            } else if (map.carte[j][i] == '1') {
                cpp = 1;
                draw_wall (renderer , i, j, cpp);
                SDL_RenderPresent(renderer);
            } else if (map.carte[j][i] == 'y') {
                cpp = 2;
                draw_player (renderer , i, j);
                SDL_RenderPresent(renderer);
            } else if (map.carte[j][i] == '@') {
                draw_bomb(renderer, i, j);
                SDL_RenderPresent(renderer); 
            }
        }
        SDL_RenderPresent(renderer);
    }

    if ( NULL == window )
    {
        printf("Could not create window: %c \n",SDL_GetError( ));
        return 1;
    }
    
        SDL_Event windowEvent;
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            { break; }

            if (windowEvent.type == SDL_KEYUP && windowEvent.key.repeat == 0 ) {
            switch (windowEvent.key.keysym.sym) {
                case SDLK_UP:
                    move_players(renderer ,map, &pos_x ,&pos_y, 'Z');
                    break;
                case SDLK_DOWN:
                    move_players(renderer ,map,&pos_x,&pos_y, 'S');
                    break;
                case SDLK_RIGHT:
                    move_players(renderer ,map,&pos_x,&pos_y, 'D');
                    break;
                case SDLK_LEFT:
                    move_players(renderer ,map,&pos_x,&pos_y, 'Q');
                    break;
                case SDLK_w :
                    file_bomb(&map, &pos_x,&pos_y);
                    if(check(etat_y,pos_x,pos_y) == false) etat_y = ajout_debut(etat_y,pos_x,pos_y,time(&t));
                    break;
            }
        }
        }
    }
    
    // while ( true )
    // {
    //     if ( SDL_PollEvent( &windowEvent ) )
    //     {
    //         if ( SDL_QUIT == windowEvent.type )
    //         { break; }
    //     }

    // }

    SDL_DestroyWindow( window );   
    SDL_Quit( );
    return EXIT_SUCCESS;
}