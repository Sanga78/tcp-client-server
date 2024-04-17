#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{

	// Check the command line parameters
	if (argc != 2)
	{
		perror("Check command line arguments\n");
		exit(1);
	}

	// Create a TCP socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// Check if socket creation was successful
	if (sockfd < 0)
	{
		perror("TCP socket creation failure\n");
		exit(1);
	}

	// Socket naming / setting up socket address structure
	int portno = atoi(argv[1]);			   // Convert port number from string to integer
	struct sockaddr_in saddress;		   // Structure to hold server address information
	saddress.sin_family = AF_INET;		   // Set address family to IPv4
	saddress.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
	saddress.sin_port = htons(portno);	   // Set port number in network byte order

	// Bind the socket to the server address
	int bnd = bind(sockfd, (struct sockaddr *)&saddress, sizeof(saddress));

	// Check if socket binding was successful
	if (bnd < 0)
	{
		perror("TCP socket binding failure\n");
		exit(1);
	}

	printf("TCP server now running and waiting for client to connect\n");

	// Listen to connecting clients
	listen(sockfd, 4); // Allow up to 4 clients to wait for connection

	// Accept the connected client
	struct sockaddr_in caddress;											// Structure to hold client address information
	socklen_t clientlen;													// Length of client address structure
	int newsock = accept(sockfd, (struct sockaddr *)&caddress, &clientlen); // Accept a client connection

	// Check if accept was successful
	if (newsock < 0)
	{
		perror("Accept failure\n");
		exit(1);
	}

	// Send a message to client that has been accepted
	send(newsock, "Just connected continue communicating\n", 50, 0); // Send a welcome message to the client
	printf("\n");

	char buffer[1024]; // Buffer to store data received from the client

	for (;;)
	{
		// Read from the connected client
		bzero(buffer, sizeof(buffer));			  // Clear the buffer
		recv(newsock, buffer, sizeof(buffer), 0); // Receive data from the client and store it in the buffer

		// Print what has come from client
		printf("%s\n", buffer); // Print the received data

		// Sending acknowledgement to client
		send(newsock, "The server has received your input\n", 50, 0); // Send an acknowledgment message to the client
send(newsock, buffer,sizeof(buffer),0);
	}
}
