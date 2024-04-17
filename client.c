#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check the command line parameters
    if (argc != 3)
    {
        perror("Check command line arguments\n"); // Print error message
        exit(1);                                  // Exit the program with failure status
    }

    // Create a TCP socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    if (sockfd < 0)
    {
        perror("TCP socket creation failure\n"); // Print error message
        exit(1);                                 // Exit the program with failure status
    }

    // Socket naming / setting up socket address structure
    int portno = atoi(argv[2]);            // Convert port number from string to integer
    struct sockaddr_in saddress;           // Structure to hold server address information
    saddress.sin_family = AF_INET;         // Set address family to IPv4
    saddress.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    saddress.sin_port = htons(portno);     // Set port number in network byte order

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&saddress, sizeof(saddress)) < 0)
    {
        perror("Connection to server failed\n"); // Print error message
        exit(1);                                 // Exit the program with failure status
    }

    // Receive message from server
    char buffer[1024];                       // Buffer to store received message
    bzero(buffer, sizeof(buffer));           // Clear the buffer
    recv(sockfd, buffer, sizeof(buffer), 0); // Receive message from server
    printf("Server: %s\n", buffer);          // Print received message from server

    // Communication loop
    while (1)
    {
        printf("Enter message: ");            // Prompt user to enter message
        fgets(buffer, sizeof(buffer), stdin); // Read message from user input

        // Send message to server
        send(sockfd, buffer, strlen(buffer), 0); // Send message to server

        // Receive response from server
        bzero(buffer, sizeof(buffer));           // Clear the buffer
        recv(sockfd, buffer, sizeof(buffer), 0); // Receive response from server
        printf("Server: %s\n", buffer);          // Print response from server
    }

    return 0; // Exit the program successfully
}
