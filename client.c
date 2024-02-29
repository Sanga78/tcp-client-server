
#include<strings.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
 int main(int argc,char *argv[]) {
     int sockfd, portno;
     struct sockaddr_in saddress;
     char buffer[1024];

//check commandline arguments
    if(argc!=3){
      perror("usagee: ./client <<server_ip> <port_number\n>");
      exit(1);

}


//create a tcp socket
  sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd<0){
                perror("Tcp socket creation failure\n");
                exit(1);
        }

//socket addressing
           portno = atoi(argv[2]);
        saddress.sin_family=AF_INET;
      inet_pton(AF_INET, argv[1], &saddress.sin_addr);
        saddress.sin_port=htons(portno);

//connect to the server

     if (connect(sockfd, (struct sockaddr *)&saddress,sizeof(saddress)) < 0){
        perror("connection to server failed\n");
	exit(1);

}

//receive message from server
	bzero(buffer,sizeof(buffer));
	recv(sockfd,buffer,sizeof(buffer),0);
	printf("server: %s\n",buffer);

//communication loop
	while(1){
	printf("enter message:");
	fgets(buffer,sizeof(buffer),stdin);

//send message to server
	send(sockfd,buffer,strlen(buffer),0);

//receive response from server
	bzero(buffer,sizeof(buffer));
	recv(sockfd,buffer,sizeof(buffer),0);
	printf("server: %s\n",buffer);


	}

	return 0;
  }


