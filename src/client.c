#include "../inc/includes.h"
#include "../inc/termbox.h"
static struct addrinfo *results;
static void sighandler( int signo ) {
  freeaddrinfo(results);
  exit(0);
}

int main(){
   signal(SIGINT, sighandler);
  char ipv4[20];
  char port[6];

  printf("Please enter server ipv4 address: \n");
  fgets(ipv4, 20, stdin);
  ipv4[strcspn(ipv4, "\n")] = 0;
  printf("Please enter server port: \n");
  fgets(port, 6, stdin);
   printf("connecting to %s:%s\n",ipv4,port);


   struct addrinfo hints;

   memset(&hints, 0, sizeof(hints));

   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;

   int err;
   //         getaddrinfo(address,port,...)
   if ((err = getaddrinfo(ipv4, port, &hints, &results)) != 0) {
       printf("error %d : %s\n", err, strerror(err));
       return 1;
   }

   int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
   if(sd < 0){
       printf("%s\n",strerror(errno));
       exit(1);
   }

   if ( connect(sd, results->ai_addr, results->ai_addrlen) < 0) {
       printf("Failed to connect\n");
       exit(1);
   }

   //DO STUFF
   int n;
   char buff[1025];
   while(1){
   if((n = read(sd, buff, sizeof(buff))) <= 0){
     printf("\n Connection Closed \n");
     exit(1);
   }
   printf("%s",buff);
   snprintf(buff, sizeof(buff), "hi\n");

     write(sd, buff, sizeof(buff));
     sleep(1);
}
   printf("\n%d bytes read\n",n);

   freeaddrinfo(results);
   return 0;
}
