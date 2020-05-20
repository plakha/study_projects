/************************
UID is an ID, that is unique
*************************/
#ifndef UID_H
#define UID_H

#include <sys/time.h> /* struct timeval */
#include <sys/types.h> /* size_t */

struct unid
{
	pid_t pid;
	struct timeval time;
	size_t counter;
};

typedef struct unid unid_t;

extern const unid_t bad_uid; /* "null" value of Unique ID */

/* Returns Unique ID by value */
unid_t UIDCreate();

/* return TRUE if to uids are same */
int UIDIsSame(unid_t uid1, unid_t uid2);

/* return TRUE if uid is "null" */
int UIDIsBad(unid_t uid);

#endif

