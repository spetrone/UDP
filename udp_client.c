/* 
Stephanie Petrone
May 29, 2021

UDP server for UDP app
*/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8989
#define MAXLEN 128

int main( int argc, char * argv[])
{
    struct sockaddr_in servAddr, clientAddr;
    int sockid;
    int count = 0;
    char recBuf[MAXLEN];
    int bindStatus = -1;

// command line input validation
if(argc != 2)
{
	printf("proper use: ./program serverport\n");
	return -1;
}


//create socket
    if((sockid = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Error with socket(): \n");
        return -1;
    }
    else printf("\n Socket created\n");

    //set client address information
    memset(&clientAddr, '0', sizeof(clientAddr));
    clientAddr.sin_port = htons(PORT);
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind
    if((bindStatus = bind(sockid,(struct sockaddr *)&clientAddr, sizeof(clientAddr))) == -1)
    {
        perror("Error with bind(): ");
        return -1;
    }

    //set server address information
    memset(&servAddr, '0', sizeof(servAddr));
    servAddr.sin_port = htons(atoi(argv[1]));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);




	return 0;
}
