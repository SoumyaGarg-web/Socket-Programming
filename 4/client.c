#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

void error(char *msg){
	
	perror(msg);
	exit(0);
}
int main(int argc, char *argv[]){
	int sockfd, portno,n;
	char buffer[256];
	
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	
	if(argc < 3){
		fprintf(stderr,"usage %s hostname port\n",argv[0]);
		exit(0);
	}
	
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0){	
		error("Error opening socket");
	}
	
	// to get ip address of server;
	server = gethostbyname(argv[1]);
	
	if(server==NULL){
		fprintf(stderr,"Error, no such host\n");
		exit(0);
	}
	
	bzero((char*) &serv_addr,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	
	bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
	
	serv_addr.sin_port = htons(portno);
	
	if(connect(sockfd,&serv_addr,sizeof(serv_addr))<0)
		error("Error on connecting");
	
	// Now ask for a message from the user, this message will be read by server
	int i=0;
	while(i==0){
	   printf("Enter two number for addition in this pattern x + x \n");
	   bzero(buffer,256);
	   fgets(buffer,255,stdin);

	   /* Send message to the server */
	   n = write(sockfd, buffer, strlen(buffer));

	   if (n < 0)
	   	error("Error writing to socket");

	   /* Now read server response */
	   bzero(buffer,256);
	   n = read(sockfd, buffer, 255);

	   if (n < 0)
	   	error("Error writing to socket");

	   printf("%s\n",buffer);
	   
	   if ((strncmp(buffer, "q", 1)) == 0) {
		printf("Client Exit...\n");
		break;
	    }
	}
	return 0;
}
