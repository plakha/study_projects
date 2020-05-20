/***********************************
Data Structure Unique ID (UID)
13/6/2019
Author Andrei
Reviewer Sandra
***********************************/

#include <assert.h> /* assert */
#include <unistd.h> /* getpid */
#include <time.h> /* gettime */

#include "uid.h" /* unid_t */

/*struct unid*/
/*{*/
/*	pid_t pid;*/
/*	struct timeval time;*/
/*	 size_t counter;*/
/*};*/

/*typedef struct unid unid_t;*/

const unid_t bad_uid;/* in linking time, inits to {0, {0, 0}, 0}; */

unid_t UIDCreate()
{
	static size_t counter = 0;
	unid_t uid = bad_uid;
	uid.pid = getpid();
	gettimeofday( &uid.time, NULL);
	uid.counter = counter++;
	
	return uid;
}

int UIDIsSame(unid_t uid1, unid_t uid2)
{
	return uid1.pid == uid2.pid
		&& uid1.time.tv_sec == uid2.time.tv_sec
		&& uid1.time.tv_usec == uid2.time.tv_usec
		&& uid1.counter == uid2.counter;
}

int UIDIsBad(unid_t uid)
{
	return UIDIsSame(uid, bad_uid);
}
