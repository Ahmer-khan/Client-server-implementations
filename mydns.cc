#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <errno.h>
#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
int main(int argc , char *argv[])
{int hstnam_to_ip(char * , char *);
  // define your variables here
   struct hostnet *hstnm;
  // check that there are enough parameters
  if (argc != 2)
    {
      fprintf(stderr, "Usage: mydns <hostname>\n");
      exit(-1);
    }
  // Address resolution stage by using gethostbyname()
  // Write your code here!
char *hostname = argv[1];
char ip[100];
hstnam_to_ip(hostname , ip);
}
  // Print to standard output
int hstnam_to_ip(char *hostname , char* ip)
{ 
  struct hostent *he;
  struct in_addr **addr_list;
int i;
if ( (he = gethostbyname( hostname ) ) == NULL)
{
  herror("gethostbyname");
  return 1;
}
printf("official name is: %s\n", he->h_name);
printf("  IP address: ");
addr_list =(struct in_addr **) he->h_addr_list;
for(i=0; addr_list[i] !=NULL; i++)
{
printf("%s ", inet_ntoa(*addr_list[i]));
return 0;
}
printf("\n");
  return 1;
}
