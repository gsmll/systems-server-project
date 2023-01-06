#include "../inc/termbox.h"
#include "../inc/utiltype.h"
#include "hangman.h"

void localgame()
{
	const int word_fd = open_with_unwrap(WORDS, O_RDONLY);
	usize size_of_word_fd = get_size_in_bytes(WORDS);
	u8* _word_buffer = malloc(size_of_word_fd);
	UNWRAP(read(word_fd, _word_buffer, size_of_word_fd), "Error: Unable to read file");
	fprintf(stdout, "%s", _word_buffer);
}


int main(int argc, char **argv) 
{ 
	if (argc < 2) { print_help(); } 

	Conf config = 
	{
		.gametype = LOCAL, 
		.username = "Stack_Smasher",
		.word_file_path = WORDS
	};


	debug_print_config(&config);
	if (config.gametype == LOCAL) 
	{
		localgame();
	}

	return 0;
}
