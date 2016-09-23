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
	struct sockaddr_in servAddr, cliAddr;
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
	servAddr.sin_port = htons (servPort);
#if 0
	inet_pton (AF_INET, servName, &servAddr.sin_addr);
#else
	inet_aton (servName, &servAddr.sin_addr);
#endif
	//Create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		perror("Error: socket failed!");
		exit(1);
	}
#if 0
    memset(&cliAddr, 0, sizeof(cliAddr));
    cliAddr.sin_family = AF_INET;
    inet_pton (AF_INET, "localhost", &cliAddr.sin_addr);
    bind(s, (struct sockaddr *)&cliAddr, sizeof(cliAddr));
#endif
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


