#include <stdio.h> /* printf */

#include "uid.h" /* pq_t */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \


int TestUID()
{
	unid_t uid1 = UIDCreate();
	unid_t uid2 = UIDCreate();
	int ret = 0;
	
	printf("uid1 pid %d\n", uid1.pid);
	printf("uid1 sec %ld\n", uid1.time.tv_sec);
	printf("uid1 usec %ld\n", uid1.time.tv_usec);
	printf("uid1 counter %lu\n", uid1.counter);

	printf("uid2 pid %d\n", uid2.pid);
	printf("uid2 sec %ld\n", uid2.time.tv_sec);
	printf("uid2 usec %ld\n", uid2.time.tv_usec);
	printf("uid2 counter %lu\n", uid2.counter);
	
	if(!UIDIsSame(bad_uid, bad_uid)
	|| UIDIsSame(uid1, uid2)
	|| !UIDIsSame(uid2, uid2))
	{
		ret = 1;
		puts("IsSame FAIL");
	}
	
	if(!UIDIsBad(bad_uid) || UIDIsBad(uid1))
	{
		ret = 1;
		puts("IsBad FAIL");
	}
	printf("Is bad same as bad? %d\n", UIDIsSame(bad_uid, bad_uid));
	
	printf("Is bad bad? %d\n", UIDIsBad(bad_uid));
	
	printf("Is uid1 bad? %d\n", UIDIsBad(uid1));
	
	printf("Is uid1 same as uid2? %d\n", UIDIsSame(uid1, uid2));
	
	printf("Is uid2 same as uid2? %d\n", UIDIsSame(uid2, uid2));
	
	
	return ret;
}

int main()
{
	RUN_TEST(TestUID);
	
	return 0;
}
	
