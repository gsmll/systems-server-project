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

int
main(int argc, char **argv) 
{
	const char *src_word = "Hello"; 
	uintptr_t src_word_len = strlen("Hello");

	char *answer = malloc(sizeof(char) * strlen("Hello") + 1);
	guess_word_buffer = calloc(src_word_len + 1, sizeof(char));

	strncpy(answer, src_word, src_word_len + 1);
	for (uintptr_t i = 0; i < src_word_len; i++)
	{
		answer[i] = '.';
	}

	while (strchr(answer, '.') != NULL) 
	{
		printf("Gameinfo\n\tchar_guesses: %zu\n\tword_guesses: %zu\n\tAnswer: %s\n", 
				character_guesses,
				word_guesses, 
				answer);
		printf("Character guess or word guess [c/w]: ");
		fgets(guess_type_buffer, 8, stdin);
		switch (guess_type_buffer[0]) 
		{
			case 'c':
				printf("Enter a character guess: ");
				fgets(guess_character_buffer, 8, stdin);
				fprintf(stderr, "[:: %c]", guess_type_buffer[0]);
				character_guesses++;	
				for (uintptr_t i = 0; i < src_word_len; i++) 
				{
					if (tolower(guess_character_buffer[0]) == tolower(src_word[i])) 
					{
						answer[i] = tolower(guess_character_buffer[0]); 
					}
					continue;
				}
				break;
			case 'w':
				printf("Enter a word guess: "); 
				fgets(guess_word_buffer, src_word_len + 1, stdin);
				fprintf(stderr, "you guessed: %s\n", guess_word_buffer);
				for (uintptr_t i = 0; i < src_word_len; i++)
				{
					if (guess_word_buffer[i] != src_word[i])
					{
						printf("You guess incorrectly!"); 
						word_guesses++;
						continue; 
					}
					word_guesses++;
					printf("YOU WIN!\n");
					return 0;
				}
			default: 
				continue;
		}
	}
	return 0;
}





