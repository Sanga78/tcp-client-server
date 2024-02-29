

#include <sys/socket.h>
#include <strings.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
int main(int argc, char *argv[]){
	int sockfd, portno,newsock,bnd;
	struct sockaddr_in   saddress,caddress;
	socklen_t clientlen;
	char buffer[1024];
	//check commandline parameters
	if(argc!=2){
		perror("check commandline arguments\n");
		exit(1);
	}

	//create tcp socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("Tcp socket creation failure\n");
		exit(1);
	}


	//socket naming
	 portno = atoi(argv[1]);
	saddress.sin_family=AF_INET;
	saddress.sin_addr.s_addr=INADDR_ANY;
	saddress.sin_port=htons(portno);

          //binding
       bnd= bind(sockfd,(struct sockaddr *) &saddress, sizeof(saddress));

           if(bnd <0){
           perror("created tcp socket binding failure\n");
          exit(1);
             }

	printf("tcp server is now running and waiting for clients\n");

	//listenn to connecting clients
	listen(sockfd,5);

	//accept conneted clients

	 newsock = accept(sockfd,(struct sockaddr *) &caddress, &clientlen);

	if(newsock < 0){
		perror("accept failure\n");
		exit(1);
	}

	//send a message to client that has been accepted
	send(newsock,"Just connected continue communicating",50,0);
	printf("\n");

//read from the accepted clients
	for(;;){
		bzero(buffer,sizeof(buffer));
	recv(newsock,buffer,sizeof(buffer),0);

	//print what has come from the client
	printf("%s\n",buffer);

	//sending acknowledgement to the client
	send(newsock,"The server has received your input\n",50,0);



	 }
}

