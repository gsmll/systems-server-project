#ifndef HANGMAN_H
#define HANGMAN_H

#include "../inc/utiltype.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define WORDS "words"
static u8 word[64];
static u8 help_message[256] = "Usage:\n$ hangman --local/network";

enum FlagType { LOCAL, NETWORK, USERNAME, UNDEFINED };
typedef struct Conf 
{
	enum FlagType gametype; 
	u8 username[32];
	u8 word_file_path[128];
} Conf;


/* Hangman-fileio.c */
int open_with_unwrap(const char *FILE, int oflag);
usize get_size_in_bytes(const char *FILE);
str copy_file_into_buffer(const int FILE_DESC, str buffer, usize nbytes); 
str ustrncpy(str dest, str src, usize nbytes);
void print_help();

/* Hangman-flag.c */
enum FlagType match_arg_to_flag(const char *num);
str match_flag_to_str(const enum FlagType flag);


/* hangman-conf.c*/
void editconfig(enum FlagType flag, Conf* config, char **argv);
int verify_config(Conf* config);
void debug_print_config(Conf* config);

/* hangman.c */
void localgame();
int main(int argc, char **argv);


#include "hangman-conf.c"
#include "hangman-flag.c"
#include "hangman-fileio.c"

#endif