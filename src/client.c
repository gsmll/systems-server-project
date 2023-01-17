#include "../inc/includes.h"
#include "../inc/termbox.h"
#include <ctype.h>
static struct addrinfo *results;
static void sighandler( int signo ) {
  freeaddrinfo(results);
  exit(0);
}
static char guess_character_buffer[16];
static char *guess_word_buffer;
static uintptr_t word_guesses = 0; 
static uintptr_t character_guesses = 0; 


int hangman(const char* srcw,int sd) 
{
	
  char guess_type_buffer[16];
	uintptr_t src_word_len = strlen(srcw);

	char *answer = malloc(sizeof(char) * strlen("Hello") + 1);
	guess_word_buffer = calloc(src_word_len + 1, sizeof(char));
	char *wrong_char_guesses = malloc(sizeof(char) * 7);
	char **wrong_str_guesses = malloc(sizeof(char*) * 7);
	int counter = 0;
	for(int i = 0; i< 7; i++) wrong_str_guesses[i] = malloc(src_word_len+1);
		
	strncpy(answer, srcw, src_word_len + 1);
	for (uintptr_t i = 0; i < src_word_len; i++)
	{
		answer[i] = '.';
	}

	while (strchr(answer, '.') != NULL) 
	{
		char buff [1024];
		char buff2 [1024];
		int wrong_character_guesses;
		if((wrong_character_guesses=read(sd, buff, sizeof(buff))) <= 0){
			sighandler(1);
		}
		int wrong_word_guesses;
		if((wrong_word_guesses=read(sd, buff2, sizeof(buff2))) <= 0){
			sighandler(1);
		}
		buff[wrong_character_guesses]=0;
		buff2[wrong_word_guesses]=0;
	
				strcpy(wrong_char_guesses,buff+4);
		
		printf("Gameinfo\n\tchar_guesses: %d\n\tword_guesses: %zu\n\t", 
				wrong_character_guesses-4,
				word_guesses);
		printf("Wrong Guesses:\n\t");
		
		for(uintptr_t i =0; i <wrong_character_guesses-4;i++)
		{
			char * pos = strchr(srcw, tolower(wrong_char_guesses[i])) ;
			if(pos != NULL){ 
				answer[pos-srcw] = wrong_char_guesses[i]; 
				int j = 0;
				while(srcw[pos-srcw + j] == wrong_char_guesses[i] )answer[pos-srcw+j++] = wrong_char_guesses[i]; 
				wrong_char_guesses[i] = ' ';
				 counter++;
				}

			printf(" %c",wrong_char_guesses[i]);
		}
		if(strchr(answer, '.') == NULL ) {
			printf("\n\nYOU WIN!");
			sighandler(1);
		}
		if(wrong_character_guesses- counter  + (wrong_word_guesses-1)/(src_word_len+1)== 11) 
		{
			printf("YOU LOSE \n");
			sighandler(1);
		}
		printf("\t");
	for(uintptr_t i =0; i < (wrong_word_guesses-1)/(src_word_len+1);i++)
		{			
			printf(" %s",&buff2[i*(src_word_len+1)]);
			if(strcmp(&buff2[i*(src_word_len+1)],srcw) == 0){
						printf("\n\nYOU WIN!");
						sighandler(1);
				}
		}
		printf("\t\nAnswer: %s\n", answer);
	
		printf("Character guess or word guess [c/w]: ");
		fgets(guess_type_buffer, 8, stdin);

		switch (guess_type_buffer[0]) 
		{
			case 'c':
				printf("Enter a character guess: ");
				fgets(guess_character_buffer, 8, stdin);
				fprintf(stderr, "[:: %c]", guess_type_buffer[0]);
				character_guesses++;	
        		write(sd,guess_character_buffer,1);
				
				break;
			case 'w':
				printf("Enter a word guess:"); 
				fgets(guess_word_buffer, 100, stdin);
				guess_word_buffer[src_word_len] = 0;
				
			    write(sd,guess_word_buffer,src_word_len+1);
				if(strcmp(guess_word_buffer,srcw) == 0){
						printf("\n\nYOU WIN!");
						sighandler(1);
				}
				break;
			default: 
				printf("invalid letter\n");
				write(sd,"\0",1);
				continue;
		}
	}
	printf("\n\nYOU WIN!");

	return 0;
}
int main(){
   signal(SIGINT, sighandler);
  char ipv4[16];
  char port[6];

  printf("Please enter server ipv4 address: \n");
  fgets(ipv4, 16, stdin);
  ipv4[strcspn(ipv4, "\n")] = 0;
  printf("Please enter server port: \n");
  fgets(port, 6, stdin);
  getchar();
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
	    printf("%s\n",strerror(errno));
       exit(1);
   }

   //DO STUFF
   int n;
   char buff[1025];
   
   if((n = read(sd, buff, sizeof(buff))) <= 0){
     printf("\n Connection Closed \n");
	 sighandler(1);
   }
   buff[n]=0;
   printf("connected\n");
   hangman(buff,sd);

   printf("\n%d bytes read\n",n);

   freeaddrinfo(results);
   return 0;
}
