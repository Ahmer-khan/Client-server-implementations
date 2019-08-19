#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[10000];
     struct sockaddr_in serv_addr, cli_addr;
     int n,x,i;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
    x = atoi(argv[1]);
     if (x < 1024)
  {  fprintf(stderr,"port no must be between 1024 and 65535 : Success\n");
     exit(1);
  }
   printf("::starting to run server at port %s\n",argv[1]);
   printf("::creating local listener socket\n"); 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     printf("::binding socket to port %d\n",portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     printf("::starting to listen at the port\n");
     while(1){
     listen(sockfd,1);
     printf("::waiting for connection\n");
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
    else{
     char str[INET_ADDRSTRLEN]; 
    inet_ntop(AF_INET, &(cli_addr.sin_addr), str, INET_ADDRSTRLEN);
    printf("connected to: %s\t", str);
    int port = (int) ntohs(cli_addr.sin_port);        
    printf("at Port: %d\n", (int) ntohs(cli_addr.sin_port));
     send(newsockfd,"Hello \r\n",255,0);}
     bzero(buffer,10000);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("c: %s\n",buffer);
     while(strcmp(buffer, "exit")!=0)
   {
    // n = write(newsockfd,"I got your message do you have something else to say",100);
    // if (n < 0) error("ERROR writing to socket");
  // bzero(buffer,10000);
// n = recv(newsockfd,buffer,9999,0);
// if (n < 0) error("error reading from socket");
   if (strcmp(buffer,"list server") ==0)
 {
   strcpy(buffer,"\r\n");
  DIR *dp;
  struct dirent *ep;
  dp = opendir ("./");
  if (dp != NULL)
    { while (ep = readdir (dp)){
     // strcpy(buffer,"\r\n");
      n = send(newsockfd, ep->d_name, strlen(ep->d_name),0);
      n  = send (newsockfd,buffer,sizeof(buffer),0);
       if (n < 0) error("error sending to socket");}
      (void) closedir (dp);}
     // bzero(buffer,10000);
     // n = send(newsockfd,"something else you like to say \r\n", 100,0);
       // if (n < 0) error("ERROR writing to socket");
  // bzero(buffer,10000);
// n = recv(newsockfd,buffer,9999,0);
// if (n < 0) error("error reading from socket");
// printf("c:%s\n", buffer);}
   // bzero(buffer,10000);
    // n = recv(newsockfd,buffer,9999,0);
// if (n < 0) error("error reading from socket");
  // printf("c:%s\n", buffer);  }
  else
    perror ("Couldn't open the directory");
}
 n = write(newsockfd,"I got your message do you have something else to say \r\n",100);
     if (n < 0) error("ERROR writing to socket");
   bzero(buffer,10000);
 n = recv(newsockfd,buffer,9999,0);
 if (n < 0) error("error reading from socket");
 printf("c:%s\n", buffer);
//bzero(buffer,10000);
// n = recv(newsockfd,buffer,9999,0);
// if (n < 0) error("error reading from socket");
// printf("c:%s\n", buffer);
 }
 printf("the client has disconnected\n"); 
 n =send(newsockfd,"bye have a nice day \r\n",1000,0);
 close(newsockfd);} 
   return 0; 
}
