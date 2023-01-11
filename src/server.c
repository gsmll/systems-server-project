#define TB_IMPL
#include "../inc/includes.h"
#include "../inc/termbox.h"
static struct addrinfo * hints, * results;
static int client_socket = 0;

static void sighandler( int signo ) {
  if(client_socket != 0)
    close(client_socket);
  free(hints);
  freeaddrinfo(results);
  tb_shutdown();
  exit(0);
}
  int main(){
      tb_init();
      tb_set_input_mode(0);
      struct tb_event ev;
      tb_clear();
      int y = 0;
      signal(SIGINT, sighandler);
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
      int playercount = 0;
      while( 1){

          //wait for next client
          tb_printf(0, y, TB_GREEN, 0, "Current Players: %d",playercount);


          tb_present();
          tb_poll_event(&ev);

          client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
          playercount++;
          int client = fork();
          if(client == 0 ){
            char buff[BUFSIZE];

          while(1){

          int len;
          if((len =read(client_socket,buff,sizeof(buff))) <= 0){
            playercount--;
            break;
          }
          buff[len] =0;
          printf("%s\n",buff);
        }
      }



          //close that client
          close(client_socket);
          tb_poll_event( &ev);
            if(ev.type == TB_EVENT_KEY){
              if(ev.key == TB_KEY_CTRL_C){
                tb_shutdown();
                   exit(0);
              }
            }
      }

      tb_shutdown();
      free(hints);
      freeaddrinfo(results);
      return 0;
  }
