#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct User
{
	char nom[30];
}User;

typedef struct Great
{
	char noms[30];
}Great;


void *function(void *arg)
{
	int socket = *(int*)arg;
	char msg[] = "Taper votre message";
	User user;
	send(socket, msg, strlen(msg), 0);
	recv(socket, &user, sizeof(user), 0);
	printf("Le client : %s \n", user.nom);
	char message[] = "Bonjour";

	Great great;
	send(socket, message, strlen(msg), 0);
	recv(socket, &great, sizeof(great), 0);
	close(socket);
	free(arg);
	pthread_exit(NULL);
}

int main(void)
{
	

	int socketServer = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addrServer;
	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(30000);

	bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));
	printf("bind : %d\n", socketServer);

	listen(socketServer, 5);
	printf("listen\n");

	pthread_t threads[5];
	
	for(int i = 0; i < 5; i++)
	{
		struct sockaddr_in addrClient;
		socklen_t csize = sizeof(addrServer);
		int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
		printf("Connexion acceptée \n");

		printf("client %d\n", socketClient);

		int *arg = malloc(sizeof(int));
		*arg = socketClient;
		pthread_create(&threads[i], NULL, function, arg);
	}

	for(int i= 0; i < 5; i++)
	{
		pthread_join(threads[i], NULL);
	}


        close(socketServer);
        printf("close\n");
        return 0;
}
