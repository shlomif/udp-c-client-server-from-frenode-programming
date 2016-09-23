
//File udp_server.c

#include "headerFiles.h"


#define SERVER_PORT 5000

int main()
{
	//Declare and define variables
	int s; //Socket descriptor (reference)
	int len; //Length of string to be echoed
	char buffer[256]; //Data buffer
	struct sockaddr_in servAddr; // Server (local) socket address
	struct sockaddr_in clntAddr; // Client (remote) socket address
	int clntAddrLen; //Length of client socket address
		
	//Build local (server) socket address
	memset(&servAddr, 0, sizeof(servAddr)); //Allocate memory
	servAddr.sin_family = AF_INET; //Family field
	servAddr.sin_port = htons(SERVER_PORT); //Default port number
	servAddr.sin_addr.s_addr = htonl (INADDR_ANY);  //Default IP address
	//printf("Local server address: %s\n", servAddr.sin_addr.s_addr);
	//Create socket
	if ((s = socket (PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error: socket failed!");
		exit (1);
	}
	//Bind socket to local address and port
	if ((bind (s, (struct sockaddr*) &servAddr, sizeof (servAddr)) < 0))
	{
		perror("Error: bind failed!");
		exit(1);
	}
	for(;;) //Run forever
	{
		printf("Waiting...\n");
		//Receice string
		len = recvfrom (s, buffer, sizeof (buffer), 0, (struct sockaddr*)&clntAddr, &clntAddrLen);
		printf("Message received: %s\n", buffer);
		//Send string
		sendto(s, buffer, len, 0, (struct sockaddr*)&clntAddr, sizeof(clntAddr));
	} //for
}//main

