#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>

void error(char *msg){
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]){
	
	int sock,length,fromlen,n;
	struct sockaddr_in server,from;
	struct hostent *hp;
	char buffer[1024];
	
	if(argc<3){
		printf("ERROR, no port provided\n");
		exit(0);
	}
	
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
		error("Opening socket");
	
	server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);
	
	if(hp==0)
		error("Unknown host");
	
	bcopy((char*)hp->h_addr,(char*)&server.sin_addr,hp->h_length);
	server.sin_port = htons(atoi(argv[2]));
	length = sizeof(struct sockaddr_in);
	
	
	printf("If you want to know current date enter SEND_DATE else if you want to know current time enter SEND_TIME");
	bzero(buffer,1024);
	scanf("%s",buffer);
	n = sendto(sock,buffer,strlen(buffer),0,&server,length);
	if(n<0)
		error("sendto");
	bzero(buffer,1024);
	n = recvfrom(sock,buffer,1024,0,&from,&length);
	if(n<0)
		error("recvfrom");
	write(1,buffer,n);
	printf("\n");
	bzero(buffer,1024);
		
	
}
