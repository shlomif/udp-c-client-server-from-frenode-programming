// File udp_client.c

#include "headerFiles.h"

int main(int argc, char* argv[])
{
	//Declare and define variables
	int s;
	int len;
	char *servName;
	int servPort;
	char* string;
	char buffer[256 + 1];
	struct sockaddr_in servAddr;
	//Check and set program arguments
	if(argc != 4)
	{
		printf("Error: 3 arguments are needed! Got %d\n", argc);
		printf("[server address] [port] [message]\n");
		exit(1);
	}
	servName = argv[1];
	servPort = atoi(argv[2]);
	string = argv[3];
	printf("String = %s\n", string);
	
	//Build server socket address
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton (AF_INET, servName, &servAddr.sin_addr);
	servAddr.sin_port = htons (servPort);
	
	//Create socket
	if ((s = socket(PF_INET, SOCK_DGRAM, 0) < 0))
	{
		perror("Error: socket failed!");
		exit(1);
	}
	//Send echo string
	len = sendto(s, string, strlen(string), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
	//Receive echo string
	recvfrom(s, buffer, len, 0, NULL, NULL);
	//Print and verify echoed string
	buffer[len] = '\0';
	printf("Echo string received: %s\n", buffer);
	//fputs(buffer, stdout);
	//Close the socket
	close(s);
	//Stop the program
	exit(0);
}//main


