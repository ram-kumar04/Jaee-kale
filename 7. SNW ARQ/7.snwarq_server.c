#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000
#define N 



int main()
{
    int serversocket, clientsocket, bindstatus;
    char servermessage[256];
    struct sockaddr_in serveraddress, clientaddress;
    int client_address_len = sizeof(clientaddress);

    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket < 0)
    {
        printf("socket failed\n");
        return -1;
    }

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    bindstatus = bind(serversocket, (const struct sockaddr *)&serveraddress, sizeof(serveraddress));
    if (bindstatus < 0)
    {
        printf("binding failed\n");
        return -1;
    }
    else
    {
        printf("binding is successful\n");
    }

    listen(serversocket,100);
    printf("Waiting for client connection...\n");

    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddress, (socklen_t *)&client_address_len);
    if (clientsocket < 0)
    {
        printf("connection is rejected by server\n");
        return -1;
    }
    else
    {
        printf("connection is accepted\n");
    }

 char data[20];
    printf("Enter the data: ");
    scanf("%s", data);

    int count = 0, j = 1;
    int k = strlen(data);

    send(clientsocket, &k, sizeof(k), 0);

    for(int i = 0; i < k; i++)
    {   send(clientsocket, &data[i], sizeof(data[i]), 0);
        recv(clientsocket, &count, sizeof(count), 0);
        //j++; working partially, keep if nothing works otherwise j=1 and 2 j++ after printf in if 
        if(count == j)
        {   
            printf("\nAcknowledgement received for bit %d", j);
            j++;
        }
        else if (count!=j)
        {
            printf("\nAcknowledgement not received for bit %d resending", j);
            j++;
        }
    
    }
    close(serversocket);
    return 0;  
}

