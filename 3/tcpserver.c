#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

/*Server's Ip address should be known.
Client will request the service and server will accept the request.
1st run/start server, server will be waiting for the request,client will be sending the request.Server accepts the request and sends the response to client.*/

void error(char *msg){
	
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]){
	int sockfd, newsockfd, portno,clilen;
	char buffer[256];
	
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	if(argc < 2){
		fprintf(stderr,"ERROR,No port provided\n");
		exit(0);
	}
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0){	
		error("Error opening socket");
	}
	
	bzero((char*) &serv_addr,sizeof(serv_addr));
	
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	if(bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
		error("Error on binding");
	
	//5 = how many clients a server will be handling at a time;
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	
	newsockfd = accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
	
	if(newsockfd<0)
		error("Error on accept");
	
	bzero(buffer,256);
	
	n = read(newsockfd,buffer,255);
	
	if(n<0)
		error("Error reading from socket");
	
	printf("Here is the message : %s\n",buffer);
	
	n = write(newsockfd,"I got your message",18);
	
	if(n<0)
		error("Error writing to socket");
	
	return 0;
	
	
}
