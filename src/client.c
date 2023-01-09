#include "../inc/includes.h"

int main(int argc, char *argv[]){
    if(argc < 3) {
       printf("Provide server address and port as a parameters\n");
       exit(1);
   }
   printf("connecting to %s:%s\n",argv[1],argv[2]);


   struct addrinfo hints, *results;
   memset(&hints, 0, sizeof(hints));

   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;

   int err;
   //         getaddrinfo(address,port,...)
   if ((err = getaddrinfo(argv[1], argv[2], &hints, &results)) != 0) {
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

   if(n = read(sd, buff, sizeof(buff)) <= 0){
     printf("\n Read error \n");
     exit(1);
   }
   printf("%s",buff);
   snprintf(buff, sizeof(buff), "hi\n");
   while(1){
     write(sd, buff, sizeof(buff));
     sleep(1);
}
   printf("\n%d bytes read\n",n);

   freeaddrinfo(results);
   return 0;
}
