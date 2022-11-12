#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct User
{
    char nom[30];

} User;

int main(void)
{

    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addresseClient;
    addresseClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    addresseClient.sin_family = AF_INET;
    addresseClient.sin_port = htons(60606);
    connect(socketClient, (const struct sockaddr *)&addresseClient, sizeof(addresseClient));
    printf("connecté au serveur\n");
    User user;
    char message[35];

    recv(socketClient, &message, 32, 0);
    printf("%s\n", message);
    scanf("%s", user.nom);
    send(socketClient, &user, sizeof(user), 0);

    close(socketClient);

    return 0;
}