#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void error(char *msg){
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]){
	
	int sock,length,fromlen,n;
	struct sockaddr_in server,from;
	char buf[1024];
	
	if(argc<2){
		fprintf(stderr, "ERROR, no port provided\n");
		exit(0);
	}
	
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
		error("Opening socket");
	
	length = sizeof(server);
	bzero(&server,length);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	
	if(bind(sock,(struct sockaddr*)&server,length)<0)
		error("binding");
	fromlen = sizeof(struct sockaddr_in);
	
	// variables to store date and time components
		int hours, minutes, seconds, day, month, year;

		// time_t is arithmetic time type
		time_t now;

		// Obtain current time
		// time() returns the current time of the system as a time_t value
		time(&now);

		// localtime converts a time_t value to calendar time and
		// returns a pointer to a tm structure with its members
		// filled with the corresponding values
		struct tm *local = localtime(&now);

		hours = local->tm_hour;	  	// get hours since midnight (0-23)
		minutes = local->tm_min;	 	// get minutes passed after the hour (0-59)
		seconds = local->tm_sec;	 	// get seconds passed after minute (0-59)

		day = local->tm_mday;			// get day of month (1 to 31)
		month = local->tm_mon + 1;   	// get month of year (0 to 11)
		year = local->tm_year + 1900;	// get year since 1900
		
		char h[100]; 
		char m[50];
		char s[50];
		sprintf(h, "%02d", hours); 
		sprintf(m, "%02d", minutes);
		sprintf(s, "%02d", seconds);
		strcat(h,":");
		strcat(h,m);
		strcat(h,":");
		strcat(h,s);
		
		char d[100]; 
		char mon[50];
		char y[50];
		sprintf(d, "%02d", day); 
		sprintf(mon, "%02d", month);
		sprintf(y, "%02d", year);
		strcat(d,"/");
		strcat(d,mon);
		strcat(d,"/");
		strcat(d,y);
	
	while(1){
		n = recvfrom(sock,buf,1024,0,(struct sockaddr*)&from,&fromlen);
		if(n<0)
			error("recvfrom");
		if(memcmp( buf, "SEND_TIME", 9) == 0 ){
			printf("\nClient is asking TIME\n");
			n = sendto(sock,h,strlen(h),0,(struct sockaddr*)&from,fromlen);
			if(n<0)
				error("sendto");
			bzero(buf,1024);
		}
		else{
			printf("\nClient is asking DATE\n");
			n = sendto(sock,d,strlen(d),0,(struct sockaddr*)&from,fromlen);
			if(n<0)
				error("sendto");
			bzero(buf,1024);
		}
	
	}
}
