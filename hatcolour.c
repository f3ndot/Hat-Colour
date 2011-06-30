#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char **argv) {

	int c;	/* option character */
	int do_name, do_help, do_version;	/* flag variables */
	char *person_name;

	struct option longopts[] = {
		{ "alice",	no_argument,		NULL,		'a' },
		{ "name",	required_argument,	NULL,		'n' },
		{ "help",	no_argument,		&do_help,	1   },
		{ "version",	no_argument,		&do_version,	1   },
		{ 0, 0, 0, 0 }
	};

	while((c = getopt_long(argc, argv, "an:vh", longopts, NULL)) != -1 ) {
		switch(c) {
		case 'a':
			do_name = 1;
			person_name = "Alice";
			break;
		case 'n':
			do_name = 1;
			person_name = optarg;
			break;
		case 'h':
			do_help = 1;
			break;
		case 'v':
			do_version = 1;
			break;
		case 0:		/* getopt_long() sets a variable, just keep going */
			break;
	#if 0
		case 1:
			break;
	#endif
		case ':':
		case '?':
		default:
			break;
		}
	}

	if(do_help == 1) {
		printf("Usage: %s [-a] [-n name] colour\n\n", argv[0]);

		puts("Perform & demonstrate basic getopt_long(3) functionality\n");

		puts("  -a, --alice		make 'Alice' as the hat owner");
		puts("  -n name, --name=name	specify hat owner's name");
		puts("  -h, --help		display this help and exit");
		puts("  -v, --version		display version information and exit\n");

		puts("Options '-a' and '-n' override each other. If both options are present,\nlatest option will be used\n");

		puts("Report bugs to: <hatcolour@justinbull.ca>");
		exit(EXIT_SUCCESS);
	}

	if(do_version == 1) {
		puts("Hat Colour 1.0");
		puts("Perform & demonstrate basic getopt_long(3) functionality\n");

		puts("Copyright (C) 2011 Justin Bull");
		puts("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>");
		puts("This is free software: you are free to change and redistribute it.");
		puts("There is NO WARRANTY, to the extent permitted by law.");
		exit(EXIT_SUCCESS);
	}

	char *hat_colour = argv[optind];	/* get the hat colour argument */

	if(hat_colour == NULL) {
		fprintf(stderr, "%s: Missing argument\nTry '%s --help' for more information.\n", argv[0], argv[0]);
		exit(EXIT_FAILURE);
	}

	if(do_name == 1)
		printf("%s's hat colour is %s\n", person_name, hat_colour);
	else
		printf("The hat colour is %s\n", hat_colour); 

	exit(EXIT_SUCCESS);

}
