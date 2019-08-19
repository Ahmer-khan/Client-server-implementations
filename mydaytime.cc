#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
#define PORT "13" // port of daytime server

void *get_socket_address(struct sockaddr *sckt)
{
   if (sckt->sa_family == AF_INET)
   {
     return &(((struct sockaddr_in*)sckt)->sin_addr);
   }
}

int main(int argc, char *argv[])
{
  // define your variables here
     int socketd,bytes;
     char buf[BUFLEN];
     struct addrinfo hints, *servinfo, *y;
     int r;
     char s[INET6_ADDRSTRLEN];

  // check that there are enough parameters
  if (argc != 2)
    {
      fprintf(stderr, "Usage: mydaytime <hostname>\n");
      exit(1);
    }

  // Write your code here
memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
if ((r = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        return 1;
    }
for(y = servinfo; y != NULL; y = y->ai_next) {
        if ((socketd = socket(y->ai_family, y->ai_socktype,
                y->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

if (connect(socketd, y->ai_addr, y->ai_addrlen) == -1)
 {
            close(socketd);
            perror("client: connect");
continue;
  }
break;
}

 if (y == NULL)
 {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
 }
inet_ntop(y->ai_family, get_socket_address((struct sockaddr *)y->ai_addr),
            s, sizeof s);
    printf("fetching time from %s\n", s);

    freeaddrinfo(servinfo);
if ((bytes = recv(socketd, buf, BUFLEN-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }
buf[bytes] = '\0';

    printf("the time is: '%s'\n",buf);

    close(socketd);
 return 0;
}
