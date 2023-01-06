#include "hangman.h"



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
	printf("Username: %s\n", config->username);	
}
