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

int main()
{
	struct sockaddr_in servAddr, clientAddr;
	int sockid;
	int count = 0;
	char recBuf[MAXLEN];
	int bindStatus = -1;
	socklen_t sockSize; //used for sendto and recfrom

 	//create socket
	if((sockid = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("Error with socket(): \n");
		return -1;
	}
	else printf("\n Socket created\n");
 
    //set server address information
	memset(&servAddr, '0', sizeof(servAddr));
    servAddr.sin_port = htons(PORT);
    servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
	//bind
	if((bindStatus = bind(sockid,(struct sockaddr *)&servAddr, sizeof(servAddr))) == -1)
	{
		perror("Error with bind(): ");
		return -1;
	}

	//receive message
	for(;;)
	{
		memset(recBuf, '\0', sizeof(recBuf));
		sockSize = sizeof(clientAddr);
		if (count = recvfrom(sockid, recBuf, sizeof(recBuf), 0, (struct sockaddr *)&clientAddr, sockSize) < 0)
		{
			perror("Error with recFrom(): ");
			return -1;
		}
		else
			printf("\nReceived %d bytes from client\n", count);

		//print echo message
		printf("\n\nECHO message: \n %s \n", recBuf);

		//echo message back to client
		sockSize = sizeof(clientAddr);
		if (count = sendto(sockid, recBuf, sizeof(recBuf), 0, (struct sockaddr *)&clientAddr, sockSize) < 0)
		{
			perror("Error with sendTo(): ");
			return -1;
		}
		else
			printf("\nSent  %d bytes from client\n", count);




	}

	
	close(sockid);

	return 0;
}
