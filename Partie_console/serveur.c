#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "Map.h"
#include "file.h"
#include <assert.h>

typedef struct User
{
    char nom[30];

} User;

void *communication(void *arg)
{
    User user;
    int socket = *(int *)arg;
    const char message[] = "donner votre nom d'utilisateur";
    send(socket, message, strlen(message) + 1, 0);
    recv(socket, &user, sizeof(user), 0);
    printf("l'utilisateur %s a rejoint le serveur \n ", user.nom);
    close(socket);
    free(arg);
    pthread_exit(NULL);
}

int main(void)
{
    char message[100] = {0};
    int sock;
    pthread_t thread_du_client;

    // AF_INET pour dire quon est en ipv4
    int socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrServer;
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    // htons pour le port
    addrServer.sin_port = htons(60606);
    bind(socketServeur, (struct sockaddr *)&addrServer, sizeof(addrServer));
    printf(" connecté id du serveur : %d\n", socketServeur);

    // listen permet au serveur d'ecouter des coonection au max le backlog
    // l'entier passé en param
    printf("en attente de connexion\n");
    listen(socketServeur, 4);
    // je creer 4 trhread qui va gerer les 4 client connecté a rendre dynamique en ligne de commande lorsque le jeux sera mis en place
    //(argv et arc en paramettre du main
    pthread_t thread[4];
    for (int i = 0; i < 4; i++)
    {
        struct sockaddr_in addrClient;
        socklen_t size = sizeof(addrClient);
        int sockClient = accept(socketServeur, (struct sockaddr *)&addrClient, &size);
        printf("connexion etablie \n");
        printf(" socket client: %d\n", sockClient);
        char client_message[200]= {0};
        memset(client_message, '\0', sizeof client_message);
        memset(message, '\0', sizeof message);
        if (i ==  0) {
            strcpy(message,"BOMBERMAN\n");
            // Send some data
            if( send(sockClient, message, strlen(message), 0) < 0)
            {
                printf("Send failed");
                return 1;
            }
        }
        // reserver un emplacement memoir pour chaque processus client
        int *arg = malloc(sizeof(int));
        *arg = sockClient;
        pthread_create(&thread[i], NULL, communication, arg);
    }
    // on join chaque thread pour eviter de close la connexion avant meme
    // que les thread s'execute
    for (int i = 0; i < 4; i++)
    {
        pthread_join(thread[i], NULL);
    }

    // cest un pointeur generique donc on lui pass ça en addresse dans le send

    // User user = {
    //     .nom = "Arthur",
    //     .age = 19,
    // };

    // send(sockClient, &user, sizeof(user), 0);

    close(socketServeur);
    // close(sockClient);
    printf("close\n");

    return 0;
}
