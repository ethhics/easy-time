#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void panic(char *err);

typedef long double ld;

/* date.c */
time_t easy_date(time_t *t);
long easy_sec_since_midnight(time_t *t);

/* geo.c */
time_t easy_sunrise(ld latitude, ld longitude, time_t date);
time_t easy_sunset(ld latitude, ld longitude, time_t date);

/* time.c */
void easy_time(ld latitude, ld longitude, time_t *t, struct tm *et);
