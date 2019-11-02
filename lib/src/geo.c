#include "../easy-time.h"
#include <math.h>

#define M_PI 3.141592653589793238462643383279

#define sindl(X)  sinl(M_PI/180.0L*X)
#define cosdl(X)  cosl(M_PI/180.0L*X)
#define unixtojulian(X) (((X) / 86400.0L) + 2440587.5L)
#define juliantounix(X) (((X) - 2440587.5L) * 86400.0L)

ld
easy_solar_noon(ld longitude, time_t date)
/* calculates solar noon in julian date */
{
	ld n, jstar, m, c, lambda;
	/* Thank you Wikipedia for being an open source of information */

	/* Current Julian day since the millenium*/
	n = unixtojulian(date) - 2451545.0L + 0.0008L;

	/* Mean solar noon */
	jstar = n - longitude / 360.0L;

	/* Solar mean anomaly */
	m = (357.5291L + 0.98560028L * jstar);
	while (m > 360.0L)
		m -= 360.0L;

	/* Equation of the center */
	c = 1.9148L*sindl(m) + 0.0200L*sindl(2*m) + 0.0003L*sindl(3*m);

	/* Ecliptic longitude */
	lambda = m + c + 180.0L + 102.9372L;
	while (lambda > 360.0L)
		lambda -= 360.0L;

	return 2451545.0 + jstar + 0.0053L*sindl(m) - 0.0069*sindl(2*lambda);
}

ld
easy_hour_angle(ld latitude, ld longitude, time_t date)
/* calculates hour angle in degrees */
{
	ld n, jstar, m, c, lambda, delta;
	/* Thank you Wikipedia for being an open source of information */

	/* Current Julian day since the millenium*/
	n = unixtojulian(date) - 2451545.0L + 0.0008L;

	/* Mean solar noon */
	jstar = n - longitude / 360.0L;

	/* Solar mean anomaly */
	m = (357.5291L + 0.98560028L * jstar);
	while (m > 360.0L)
		m -= 360.0L;

	/* Equation of the center */
	c = 1.9148L*sindl(m) + 0.0200L*sindl(2*m) + 0.0003L*sindl(3*m);

	/* Ecliptic longitude */
	lambda = m + c + 180.0L + 102.9372L;
	while (lambda > 360.0L)
		lambda -= 360.0L;

	/* Declination of the sun */
	delta = 180.0L/M_PI * asinl(sindl(lambda)*sindl(23.44L));

	return 180.0L / M_PI *
		acosl((sindl(-0.83L) - sindl(latitude)*sindl(delta))
			/ (cosdl(latitude)*cosdl(delta)));
}

time_t
easy_sunrise(ld latitude, ld longitude, time_t date)
/* calculates sunrise on the date given by time_t date.
 * date is assumed to be midnight local time */
{
	/* if this is midnight local time, and unix time is based on utc,
	 * then I can find the offset from local to utc really easily! */
	time_t offset = date % 86400;
	ld noon = easy_solar_noon(longitude, date-offset+86400/2);
	ld hourangle = easy_hour_angle(latitude, longitude, date-offset+86400/2);

	return (time_t) (juliantounix(noon - hourangle/360.0L));
}

time_t
easy_sunset(ld latitude, ld longitude, time_t date)
/* calculates sunset on the date given by time_t */
{
	/* if this is midnight local time, and unix time is based on utc,
	 * then I can find the offset from local to utc really easily! */
	time_t offset = date % 86400;
	ld noon = easy_solar_noon(longitude, date-offset+86400/2);
	ld hourangle = easy_hour_angle(latitude, longitude, date-offset+86400/2);

	return (time_t) (juliantounix(noon + hourangle/360.0L));
}
