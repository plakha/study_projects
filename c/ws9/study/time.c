/**********************
time(NULL) checks time now, stores in time t.
gm_time stoers time_t in struct tm, thus enabling you working with time (e.g execut alarm if it is wednesday)

mk time sets time_t from struct tm
so you can difftime betweem two time_t types

           struct tm {
               int tm_sec;    /* Seconds (0-60) */
               int tm_min;    /* Minutes (0-59) */
               int tm_hour;   /* Hours (0-23) */
               int tm_mday;   /* Day of the month (1-31) */
               int tm_mon;    /* Month (0-11) */
               int tm_year;   /* Year - 1900 */
               int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
               int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
               int tm_isdst;  /* Daylight saving time */
           };

*******************/

#include <stdio.h> /* printf */
#include <time.h>

time_t sometime;
struct tm waterloo = {0, 2, 9, 30, 1, 1905};

int main()
{

	sometime = mktime(&waterloo);
	puts(ctime(&sometime));
	sometime = time(NULL);
	puts(asctime(&waterloo));
	puts(ctime(&sometime));
	gmtime_r(&sometime, &waterloo);
	puts(asctime(&waterloo));

	return 0;
}
