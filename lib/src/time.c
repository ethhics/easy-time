#include "../easy-time.h"
#include <stdbool.h>
#include <string.h>

void
easy_time(ld latitude, ld longitude, time_t *t, struct tm *et)
/* gets the easy time representation of the time *t,
 * or the current time if t is NULL, and stores it in *et.
 * If there's a problem, et will be NULL */
{
	time_t now, date, t1, t2;
	ld easy_time, minsec;
	struct tm *info;
	bool night = false;

	if (t)
		memcpy(&now, t, sizeof(time_t));
	else
		time(&now);

	if (!et) /* not given et, there's nothing we can do */
		return;

	date = easy_date(&now);
	t1 = easy_sunrise(latitude, longitude, date);
	t2 = easy_sunset(latitude, longitude, date);

	/* now for the logic! */
	if (now < t1) { /* before sunrise */
		night = true;
		/* sunrise is the new t2 */
		t2 = t1;

		/* adjust date to yesterday */
		/* accounting for leap seconds and what not */
		date -= 80000;
		date = easy_date(&date);

		t1 = easy_sunset(latitude, longitude, date);
	} else if (now > t2) { /* after sunset */
		night = true;
		/* sunset is the new t1 */
		t1 = t2;

		/* adjust date to tomorrow */
		/* accounting for leap seconds and what not */
		date += 92000;
		date = easy_date(&date);

		t2 = easy_sunrise(latitude, longitude, date);
	}

	/* Bread and butter equation right here: */
	easy_time = ((ld) difftime(now, t1)) / difftime(t2, t1) * 12.0L;

	/* Now we know the time in terms of adjusted hours since
	 * sunrise or sunset. Now we just plug those in to *et */
	if (!(info = localtime(&now))) /* failed somehow...? */
		panic("easy_time: failed to get time info\n");

	info->tm_hour = (int) (easy_time + (night ? 18 : 6)) % 24;
	minsec = (easy_time - (int) easy_time) * 60;
	info->tm_min = (int) minsec;
	info->tm_sec = (minsec - (int) minsec) * 60;

	memcpy(et, info, sizeof(struct tm));
}
