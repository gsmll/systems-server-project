#define TB_IMPL
#include "../inc/includes.h"
//#include "../inc/termbox.h"
#include <pthread.h>
#include <sys/shm.h>
#include <sys/ipc.h>
//#include "../inc/hangman.h"
static struct addrinfo * hints, * results;
static int client_socket = 0;
static  int shmid;
static  int shmid2;
static char* data ;
static char* data2 ;

static void sighandler( int signo ) {
  if(client_socket != 0)
    close(client_socket);
  free(hints);
  freeaddrinfo(results);
  shmdt(data);
  shmdt(data2);
  shmctl(shmid, IPC_RMID, 0); //remove the segment
  shmctl(shmid2, IPC_RMID, 0); //remove the segment
  exit(0);
  
}

  int main(){

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
     
      shmid = shmget(233811181, 10, IPC_CREAT | 0640); //create and access
      data=shmat(shmid, 0, 0);
      shmid2 = shmget(233811182, 1024, IPC_CREAT | 0640); //create and access
      data2=shmat(shmid2, 0, 0);
      data[0]= 0;
      data[1] = 1;
      data[2] = 4;
      data[3] = 0;
      while( 1){
          //wait for next client
          
            printf("\n");

  
          

          client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
         
          data[0]++;
             printf("Player Joined - %d Current Players\n",data[0]);
          int client = fork();
          if(client == 0 ){
            int id = data[0];
            printf("id: %d\n",data[0]);
            char buff[BUFSIZE] ;
            snprintf(buff, 6, "hello");
            write(client_socket, buff, sizeof(buff));


          while(1){
            if (id > data[0]) id += (data[0] - id);
            printf("%d %d\n",data[1],id);
            while(data[1] != id){
              sleep(1);
              printf("sleeping\n");
            }
            printf("%d\n",data[2]);
            usleep(500000);
            write(client_socket, data, data[2]);
          int len;
          if((len =read(client_socket,buff,sizeof(buff))) <= 0){
            data[0]--;
            if(data[1] == id) data[1] = (data[1] == (data[0]+1)) ? 1 : (data[1] + 1);
             printf("Player Left - %d Current Players\n",data[0]);
            break;
          }
          buff[len] =0;
          if(strlen(buff) == 1){
             data[data[2]++] = buff[0];
          }
          else{
            int i=0;
            while(buff[i] != 0){
              data2[(data[3]*6)+i] = buff[i++];
            }
            data2[(data[3]*6)+i] = 0;
        
            printf("word - %s\n",&data2[(data[3]++) * 6 + 1]);
          }
          data[1] = (data[1] == data[0]) ? 1 : (data[1] + 1);

        }
        }
         



          //close that client
          close(client_socket);
      }
      shmdt(data);
      shmctl(shmid, IPC_RMID, 0); //remove the segment
      shmdt(data2);
      shmctl(shmid2, IPC_RMID, 0); //remove the segment
      free(hints);
      freeaddrinfo(results);
      return 0;
  }
