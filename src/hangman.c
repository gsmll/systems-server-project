#include "../inc/termbox.h"
#include "../inc/utiltype.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Globals */
#define UNWRAP(x, y)                                                           \
  if (x < 0) {                                                                 \
    perror(y);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } else {}

#define WORDS "words"
static u8 word[64];
static u8 help_message[256] = "Usage:\n$ hangman --local/network";
static print_help() 
{
	fprintf(stderr, "%s\n", help_message);
	exit(EXIT_FAILURE);
}



enum FlagType { LOCAL, NETWORK, USERNAME, UNDEFINED };
typedef struct Conf 
{
	enum FlagType gametype; 
	u8 username[32];
	u8 word_file_path[128];
} Conf;


/* Headers */
int open_with_unwrap(const char *FILE, int oflag);
usize get_size_in_bytes(const char *FILE);
str copy_file_into_buffer(const int FILE_DESC, str buffer, usize nbytes); 
void localgame();
enum FlagType match_arg_to_flag(const char *num);
int main(int argc, char **argv);

/* impl */
int 
open_with_unwrap(const char *FILE, int oflag) 
{
	int file_desc = open(FILE, oflag); 
	UNWRAP(file_desc, "Error: Unable to open file");
	return file_desc;
}


usize 
get_size_in_bytes(const char *FILE) 
{
	usize _bytes_size;
	struct stat *stat_buffer = malloc(sizeof(struct stat));
	UNWRAP(stat(FILE, stat_buffer), "Error: Unable to get statistics of file");
	_bytes_size = stat_buffer->st_size;
	free(stat_buffer);
	return _bytes_size;
}

u8* 
copy_file_into_buffer(const int FILE_DESC, u8* buffer, usize nbytes)
{
	UNWRAP(read(FILE_DESC, buffer, nbytes), "Error: Unable to copy file into buffer");
	return buffer;
}


void 
localgame()
{
	const int word_fd = open_with_unwrap(WORDS, O_RDONLY);
	usize size_of_word_fd = get_size_in_bytes(WORDS);
	u8* _word_buffer = malloc(size_of_word_fd);
	UNWRAP(read(word_fd, _word_buffer, size_of_word_fd), "Error: Unable to read file");
	fprintf(stdout, "%s", _word_buffer);
}

str match_flag_to_str(const enum FlagType flag)
{
	switch (flag) 
	{
		case LOCAL:
			return (str) "local";
		case NETWORK:
			return (str) "network";
		case USERNAME:
			return (str) "username:";
		case UNDEFINED:
			return (str) "undefined";
	}
}


enum FlagType match_arg_to_flag(const char *arg)
{
	enum FlagType flag;
	if (strcmp(arg, "--local") == 0) 
	{
		flag = LOCAL;
	} 
	else if (strcmp(arg, "--network") == 0) 
	{
		flag = NETWORK;
	}
	else if (strcmp(arg, "--username") == 0) 
	{
		flag = USERNAME;
	}
	else 
	{
		flag = UNDEFINED;
	}
	return flag;
}

str ustrncpy(str dest, str src, usize nbytes) 
{
	usize i = 0;
	while (i < nbytes) 
	{
		dest[i] = src[i];
		i++;
	}
	return dest;
}


void editconfig(enum FlagType flag, Conf* config, char **argv)
{
	switch (flag) 
	{
		case LOCAL:
			config->gametype = LOCAL;
			break;
		case NETWORK:
			config->gametype = NETWORK;
			break;
		case USERNAME:
			if (argv[1 + 1] == NULL) print_help();
			ustrncpy(config->username, (str) argv[1 + 1], strlen(argv[1 + 1]));
			break;
		case UNDEFINED: 
			print_help();
	}
}

int verify_config(Conf* config) 
{
	if (config->gametype != NETWORK || config->gametype != LOCAL) return 1;
	if (strlen((char *) config->username) < 1) return 1;  
	return 0;
} 

void debug_print_config(Conf* config)
{
	printf("Gametype: %s\n", match_flag_to_str(config->gametype));
}

int 
main(int argc, char **argv) 
{ 
	if (argc < 2) { print_help(); } 

	Conf config; 

	usize index = 1;
	while (verify_config(&config)) {
		enum FlagType flag = match_arg_to_flag(argv[index]);
		if (flag == USERNAME) index++;
		editconfig(flag, &config, argv);
		index++;
	}


	return 0;
}
