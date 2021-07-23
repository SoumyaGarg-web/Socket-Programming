#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include "arith.h"


int start_server(int);

int start_listen_client(int );

int main( int argc, char *argv[] ) {
   int sockfd, clilet_sockfd, portno;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;

   /* First call to socket() function */
   if (argc < 2) {
      printf("please enter port no ");
      exit(1);
   } 
   else
      portno = atoi(argv[1]);

   portno = atoi(argv[1]);;
   sockfd = start_server(portno);

   if (sockfd < 0) {
       perror("ERROR on accept");
      exit(1);
   }

   clilet_sockfd =  start_listen_client(sockfd);

   if (clilet_sockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }

   /* If connection is established then start communicating */
   int i =0;
   while(i==0){
   bzero(buffer,256);
   n = read( clilet_sockfd,buffer,255 );

   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   if (strncmp("q", buffer, 1) == 0) {
               printf("Server Exit...\n");
               n = write(clilet_sockfd,buffer,100);
               break;
           }

   printf("Here is the two number from client: %s\n",buffer);

   calculate(buffer);


   /* Write a response to the client */
   n = write(clilet_sockfd,buffer,100);

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }else{
        printf("data has been sent back to client \n");
   }
 }
   return 0;

}



   int start_server(int port_no){

   int sockfd;
   struct sockaddr_in serv_addr;

   // socket function
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      return -1;
      //exit(1);
   }
   /* Initialize socket structure */
   if(port_no==0){
      port_no = 8001;
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(port_no);

   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      return -1;
      //exit(1);
   }

   return sockfd;
}



int start_listen_client(int sockfd){

   int client_con,clilen;
   struct sockaddr_in cli_addr;


   listen(sockfd,5);
   clilen = sizeof(cli_addr);

   /* Accept actual connection from the client */
   client_con = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

   if (client_con < 0) {
      perror("ERROR on accept");
      return -1;
   }

   return client_con;

}
