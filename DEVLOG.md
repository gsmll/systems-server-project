# DEVLOG (Latest - Oldest)
## Devlog for January 11th 2022
This is the second formally written devlog for the Hangman project.

### Gabriel
I Finished up the base hangman game, adding a lose condition and word + character guess saving and display. I also fixed the character and word guess check mechanics as they were buggy.

Started to port hangman to client. Server now sends word to client when game starts. Now just need to add turn based gameplay across clients. 

## Devlog for January 10th 2022
This is the first formally written devlog for the Hangman project.

### Jae  
I coded up a very basic hangman program that works as aspected. 

```C
int
main(int argc, char **argv) 
{
	const char *src_word = "Hello"; 
	int src_word_len = strlen("Hello");

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
					if (guess_character_buffer[0] == src_word[i]) 
					{
						answer[i] = guess_character_buffer[0]; 
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
```

This code works as aspected as it prompts the user either for a word or a character, if the
letter is in the word, then reveal all instances of that letter in the word. If the word is 
exactly the given word, then inform the user and end the game. If invalid input is given
don't crash but restart the game loop. Number of guesses is also recorded. 

```bash
$ ./hangman
Gameinfo
	char_guesses: 0
	word_guesses: 0
	Answer: .....
Character guess or word guess [c/w]: c
Enter a character guess: l
[:: c]Gameinfo
	char_guesses: 1
	word_guesses: 0
	Answer: ..ll.
Character guess or word guess [c/w]: c
Enter a character guess: H
[:: c]Gameinfo
	char_guesses: 2
	word_guesses: 0
	Answer: H.ll.
Character guess or word guess [c/w]: c
Enter a character guess: o
[:: c]Gameinfo
	char_guesses: 3
	word_guesses: 0
	Answer: H.llo
Character guess or word guess [c/w]: w
Enter a word guess: Hello
you guessed: Hello
YOU WIN!
```

Focuses of optimization: 

```C
// Handles getting words for the game
const char *src_word = "Hello"; 
int src_word_len = strlen("Hello");
```

Currently, the word is hard-coded into RAM to be "Hello" which obviously does not 
make for a very fun and engaging hangman game. 

Possible steps for optimization: 
1. Allow the user to pick a word on program startup
2. Read from a file and pick a random word from that file. 
~~3. Randomly generate a word (basically gibberish)~~

(2) isn't actually that hard to implement but 1 is since it requires that 
we take in command line arguments. 


(2) Just have a file that contains words seperated by newline characters with a twist,
since most files nowadays are encoded to be UTF-8, we'll have to use UTF-8 strings for 
our game. This is easily implemented in C with the `unsigned char` type and `u8""`. It 
also means that all of the things that the user could input as guesses (characters/words) 
also have to be UTF-8 compatible. 


(1) What does `program startup` even mean? Well I think in this scenario I would want to 
implement a more complex environment system rather than just grabbing stdargs which is 
a little bit limiting and also time consuming. 

(1) This could be done through a ctl/ctrl interface that is not dissimilar to a lot of 
the API interfaces that things like bluetoothctl and connmanctl and wpa_cli and many others
use. This will also help us with other stuff like connecting to a game and other tasks, 
it can also help us with having a dedicated config file because who wouldn't want to have
that right? 

```Bash
[hangmanctl]# ______

help -> 

connect local/network;
set words "PATH_TO_WORDS_FILE"
set username "USERNAME"
etc.

```

```C
	char *answer = malloc(sizeof(char) * strlen("Hello") + 1);
	guess_word_buffer = calloc(src_word_len + 1, sizeof(char));

	strncpy(answer, src_word, src_word_len + 1);
	for (uintptr_t i = 0; i < src_word_len; i++)
	{
		answer[i] = '.';
	}

```

Here we set two strings: 

Owned and immutable reference to the src_word. 
Mutable reference to our guess_buffer. 

these two strings can easily be written into files to encapsulate game state. 

```C
while (strchr(answer, '.') != NULL) 	
```

This is basically how to tell whether the game has ended or not. The actual 
game logic is super simple. 

I will implement these reforms tmrw.


### Gabe

My edits weren't quite as grand as Jae's today, as I'm setting up the ui for the server.
My main goal was to learn to use the termbox 2 library, and to make the server keep track of current connected clients. 

Termbox2 intercepted intercept though, and I dont think it's possible without multithreading to handle keys without interrupting server processess so I made little progress today.
Tommorow I will just implement termbox for client and start doing hangman cross server.


