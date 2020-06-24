#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User
{
        char nom[30];

}User;

typedef struct Great
{
        char noms[30];
}Great;


int main(void)
{
        int socketClient = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in addrClient;
        addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
        addrClient.sin_family = AF_INET;
        addrClient.sin_port = htons(30000);
        connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
        printf("connecté\n");

        User user;
        char msg[50];
        recv(socketClient, msg, 48, 0);
        printf("%s\n", msg);
        scanf("%s ", user.nom);
        send(socketClient, &user, sizeof(user), 0);

        Great great;
        char message[50];
        recv(socketClient, message, 48, 0);
        printf("Le Serveur : %s\n", message);

        close(socketClient);

        return 0;
}
