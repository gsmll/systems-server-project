#include "../inc/includes.h"
#include "../inc/termbox.h"

static struct addrinfo *results;
static void sighandler( int signo ) {
  freeaddrinfo(results);
  exit(0);
}
static char guess_character_buffer[16];
static char guess_type_buffer[16];
static char *guess_word_buffer;
static uintptr_t word_guesses = 0; 
static uintptr_t character_guesses = 0; 
static uintptr_t wrong_character_guesses = 0; 
static uintptr_t wrong_word_guesses = 0; 

int hangman(const char* srcw) 
{
	
  
	uintptr_t src_word_len = strlen(srcw);

	char *answer = malloc(sizeof(char) * strlen("Hello") + 1);
	guess_word_buffer = calloc(src_word_len + 1, sizeof(char));
	char *wrong_char_guesses = malloc(sizeof(char) * 7);
	char **wrong_str_guesses = malloc(sizeof(char*) * 7);
	for(int i = 0; i< 7; i++) wrong_str_guesses[i] = malloc(src_word_len+1);
		
	strncpy(answer, srcw, src_word_len + 1);
	for (uintptr_t i = 0; i < src_word_len; i++)
	{
		answer[i] = '.';
	}

	while (strchr(answer, '.') != NULL) 
	{
		printf("Gameinfo\n\tchar_guesses: %zu\n\tword_guesses: %zu\n\t", 
				character_guesses,
				word_guesses);
		printf("Wrong Guesses:\n\t");
		if(wrong_character_guesses + wrong_word_guesses == 7) 
		{
			printf("YOU LOSE \n");
			return 0;
		}
		for(uintptr_t i =0; i <= wrong_character_guesses;i++)
		{
			printf(" %c",wrong_char_guesses[i]);
		}
		printf("\t");
		for(uintptr_t i =0; i <= wrong_word_guesses;i++)
		{			
			wrong_str_guesses[i][strcspn(wrong_str_guesses[i], "\n")] = 0;
			printf(" %s",wrong_str_guesses[i]);
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
				char exist = 0;
				for (uintptr_t i = 0; i < src_word_len; i++) 
				{
					
					if (tolower(guess_character_buffer[0]) == tolower(srcw[i])) 
					{
						answer[i] = tolower(guess_character_buffer[0]);
						exist = 1;
						continue;
					}
					if(!(i == src_word_len - 1 && !exist)) continue;
					wrong_char_guesses[wrong_character_guesses++] = toupper(guess_character_buffer[0]);
					
					
					
					
					
				}
				break;
			case 'w':
				printf("Enter a word guess: "); 
				fgets(guess_word_buffer, src_word_len + 1, stdin);
				fprintf(stderr, "you guessed: %s\n", guess_word_buffer);
				
					word_guesses++;
					if (strcasecmp(guess_word_buffer,srcw))
					{
						printf("You guess incorrectly!"); 
						strcpy(wrong_str_guesses[wrong_word_guesses++],guess_word_buffer);
						break; 
					}
					printf("YOU WIN!\n");
					return 0;
				
			default: 
				continue;
		}
	}
	return 0;
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
   
   if((n = read(sd, buff, sizeof(buff))) <= 0){
     printf("\n Connection Closed \n");
     exit(1);
   }
   buff[n]=0;
   hangman(buff);

   printf("\n%d bytes read\n",n);

   freeaddrinfo(results);
   return 0;
}
