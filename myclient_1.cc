#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
void error(const char *msg) {
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[]) {
    int sockfd, portno, n,i;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct in_addr **addr_list;
    char buffer[10000],buffer1[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
   i = atoi(argv[2]);
   if (i < 1024)
 {  fprintf(stderr,"port should be between 1024 and 65535>: Success\n");
     exit(1);}
else{printf("running client....\n");
     printf("wil try to connect to %s\t", argv[1]);
     printf("at port %s\n", argv[2]);}
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    else{printf("hostname: %s\t",server->h_name);
         printf("has IP addresses: "); addr_list = (struct in_addr **)server->h_addr_list; for(i = 0; addr_list[i] != NULL; i++) { 
printf("%s ", inet_ntoa(*addr_list[i]));}
printf("\n");}
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    else{
         bzero(buffer1,256);
         recv(sockfd,buffer1,255,0);
         printf("%s\n",buffer1);}
    printf("c: ");
    bzero(buffer,10000);
    scanf("%[^\n]%*c" ,buffer);
  while (strcmp(buffer, "exit") != 0) {
    n = send(sockfd,buffer,9999,0);
    if (n < 0)
         error("ERROR writing to socket");
    bzero(buffer,10000);
    n = recv(sockfd,buffer,9999,0);
    if (n < 0)
         error("ERROR reading from socket");
    printf("S: %s\n",buffer);
    printf("c :");
    bzero(buffer,1024);
    scanf("%[^\n]%*c" ,buffer);
}
   n = write(sockfd,buffer,9999);
   if (n < 0)
         error("ERROR writing to socket");
    bzero(buffer,10000);
    n = read(sockfd,buffer,9999);
    if (n < 0)
         error("ERROR reading from socket");
    printf("S: %s\n",buffer);
    close(sockfd);
    return 0;
}
