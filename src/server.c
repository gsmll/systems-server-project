#include "../inc/includes.h"

  int main(){
      struct addrinfo * hints, * results;
      hints = calloc(1,sizeof(struct addrinfo));

      hints->ai_family = AF_INET;
      hints->ai_socktype = SOCK_STREAM; //TCP socket
      hints->ai_flags = AI_PASSIVE; //only needed on server
      getaddrinfo(NULL, PORT, hints, &results);  //NULL is localhost or 127.0.0.1

      //create socket
      int listen_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
      bind(listen_socket, results->ai_addr, results->ai_addrlen);
      listen(listen_socket, 10);//10 clients can wait to be processed

      socklen_t sock_size;
      struct sockaddr_storage client_address;
      sock_size = sizeof(client_address);

      while(1){
          //wait for next client
          printf("Waiting for connection\n");
          int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
          int client = fork();
          if(client == 0 ){
            char buff[1025]="";
          //send the time formatted as a string
          time_t ticks = time(NULL);
  	      snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
          //send the string
          write(client_socket, buff, sizeof(buff));
          while(1){
          int len =read(client_socket,buff,sizeof(buff));
          buff[len] =0;
          printf("%s\n",buff);
        }
          }

          //close that client
          close(client_socket);
      }
      free(hints);
      freeaddrinfo(results);
      return 0;
  }
