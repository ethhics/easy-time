#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/easy-time.h"

void
usage (void)
{
	printf("Print this help: easy-time --help\n");
	printf("Show current time: easy-time latitude longitude\n");
}

int
main (int argc, char *argv[])
{
	long double latitude, longitude;
	struct tm et;

	if (argc != 3) {
		usage();
		return argc != 2; /* if 2 args, assume --help */
	}

	latitude = strtold(argv[1], NULL);
	longitude = strtold(argv[2], NULL);

	easy_time(latitude, longitude, NULL, &et);

	printf("At %Lf %Lf, it's currently %s",
	       latitude, longitude, asctime(&et));

	return 0;
}
