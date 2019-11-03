#include "../easy-time.h"
#include <string.h>

void
panic(char *err)
/* print to stderr and quit */
{
	fprintf(stderr, err);
	exit(-1);
}

time_t
easy_date(time_t *t)
/* Returns midnight on the date specified,
 * or on the current date if t is NULL */
{
	time_t now;
	struct tm *info;

	if (t)
		memcpy(&now, t, sizeof(time_t));
	else
		time(&now);
	
	if (!(info = localtime(&now))) /* This failed somehow...? */
		panic("easy_date: failed to get time info\n");

	/* set the info struct to be midnight for whatever date it is */
	info->tm_sec = 0;
	info->tm_min = 0;
	info->tm_hour = 0;

	return mktime(info);
}

long
easy_sec_since_midnight(time_t *t)
/* Gets the number of seconds since midnight
 * If t is NULL, then uses current time */
{
	time_t now;
	
	if (t)
		memcpy(&now, t, sizeof(time_t));
	else
		time(&now);
	
	return (long) difftime(now, easy_date(&now));
}
