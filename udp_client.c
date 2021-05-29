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

#define PORT 8899
#define MAXLEN 128

int main( int argc, char * argv[])
{
    struct sockaddr_in servAddr, clientAddr;
    int sockid;
    int count = 0;
	int msgLen = 0; //sential value for loop
    char recBuf[MAXLEN];
	char sendBuf[MAXLEN];
    int bindStatus = -1;
	int addrLen = sizeof(struct sockaddr_in);
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

    
	//get first input
	memset(sendBuf, '\0', sizeof(sendBuf));//initialize buffer
	printf("\nEnter your message or press -1 to exit\n");
	if(fgets(sendBuf, MAXLEN-1, stdin) < 0)
	{
		perror("Error with fgets() ");
		return -1;
	}

	//set sentinal if applicable
	if(atoi(sendBuf) == -1)
		msgLen = -1;
	else
		msgLen = strlen(sendBuf);

	//loop until sentinel
	while(msgLen  != -1)
	{
		//send to server
		if((count = sendto(sockid, sendBuf, msgLen, 0, (struct sockaddr *)&servAddr, addrLen)) < 0)
		{
			perror("Error with sendto() ");
			return -1;
		}

		//print info
		printf("\nSent %d bytes to the server\n", count);


		//receive from server and print echo
		memset(recBuf, '\0', sizeof(recBuf));
		if((count = recvfrom(sockid, recBuf, sizeof(recBuf), 0, (struct sockaddr *)&servAddr, (socklen_t *)&addrLen)) < 0)
		
		{
			perror("Error with recFrom() ");
			return -1;
		}

		printf("\nEcho message size % d received:\n", count);
		printf("%s\n\n", recBuf);
	
		//get new value
		memset(sendBuf, '\0', sizeof(sendBuf));//initialize buffer
		printf("\nEnter your message or press -1 to exit\n");
		if(fgets(sendBuf, MAXLEN-1, stdin) < 0)
		{
			perror("Error with fgets() ");
			return -1;
		}

		//set sentinal if applicable
		if(atoi(sendBuf) == -1)
			msgLen = -1;
		else
			msgLen = strlen(sendBuf);
	}
	
	return 0;
}
