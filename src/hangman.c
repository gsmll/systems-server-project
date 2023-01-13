#include <stdio.h> 
#include <stdint.h> 
#include <stdlib.h> 
#include <getopt.h> 
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define THROW_ERR(x) { perror(x); exit(EXIT_FAILURE); } 


static char guess_character_buffer[16];
static char guess_type_buffer[16];
static char *guess_word_buffer;
static uintptr_t word_guesses = 0; 
static uintptr_t character_guesses = 0; 
static uintptr_t wrong_character_guesses = 0; 
static uintptr_t wrong_word_guesses = 0; 

int main(int argc, char **argv) 
{
	const char *src_word = "Hello"; 
	uintptr_t src_word_len = strlen("Hello");

	char *answer = malloc(sizeof(char) * strlen("Hello") + 1);
	guess_word_buffer = calloc(src_word_len + 1, sizeof(char));
	char *wrong_char_guesses = malloc(sizeof(char) * 7);
	char **wrong_str_guesses = malloc(sizeof(char*) * 7);
	for(int i = 0; i< 7; i++) wrong_str_guesses[i] = malloc(src_word_len+1);
		
	strncpy(answer, src_word, src_word_len + 1);
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
					
					if (tolower(guess_character_buffer[0]) == tolower(src_word[i])) 
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
					if (strcasecmp(guess_word_buffer,src_word))
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





