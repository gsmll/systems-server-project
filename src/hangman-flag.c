#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/utiltype.h"
#include "hangman.h"


u8* match_flag_to_str(const enum FlagType flag)
{
	switch (flag) 
	{
		case LOCAL:
			return (str) u8"local";
		case NETWORK:
			return (str) u8"network";
		case USERNAME:
			return (str) u8"username:";
		case UNDEFINED:
			return (str) u8"undefined";
	}
	return (str) u8"";
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