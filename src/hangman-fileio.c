#include "../inc/utiltype.h"
#include "hangman.h"
#include <unistd.h>

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


void print_help() 
{
	fprintf(stderr, "%s\n", help_message);
	exit(EXIT_FAILURE);
}