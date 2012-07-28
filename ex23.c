#include <stdio.h>
#include <string.h>
#include "debug.h"

int normal_copy(char *from, char *to, int count)
{
	int i = 0;

	for(i = 0 ; i < count ; i++)
	{
		to[i] = from[i];
	}

	return i;
}

int duffs_device(char *from, char *to, int count)
{
	{
		int n = (count + 7) / 8;

		switch(count % 8) {
			case 0: do { *to++ = *from++;
						case 7: *to++ = *from++;
						case 6: *to++ = *from++;
						case 5: *to++ = *from++;
						case 4: *to++ = *from++;
						case 3: *to++ = *from++;
						case 2: *to++ = *from++;
						case 1: *to++ = *from++;
					} while(--n > 0);
		}
	}

	return count;
}

int zeds_device(char * from, char *to, int count)
{
	{
		int n = (count + 7) / 8;

		switch(count % 8){
			case 0:
			again: *to++ = *from++;

			case 7: *to++ = *from++;
			case 6: *to++ = *from++;
			case 5: *to++ = *from++;
			case 4: *to++ = *from++;
			case 3: *to++ = *from++;
			case 2: *to++ = *from++;
			case 1: *to++ = *from++;
					if(--n > 0) goto again;
		}
	}

	return count;
}

int valid_copy(char *data, int count, char expects)
{
	int i = 0;
	for(i = 0 ; i < count ; i++){
		if(data[i] != expects){
			log_err("[%d] %c != %c", i, data[i], expects);
			return 0;
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	char from[9] = {'a'};
	char to[9] = {'c'};
	int rc = 0;

	memset(from, 'x', 9);
	memset(to, 'y', 9);
	check(valid_copy(to, 9, 'y'), "Not intialized right.");

	rc = normal_copy(from, to, 9);
	check(rc == 9, "Normal copy failed %d", rc);
	check(valid_copy(to, 9, 'x'), "Normal copy failed");

	memset(to, 'y', 9);

	rc = duffs_device(from, to, 9);
	check(rc == 9, "Duff's Device copy failed %d", rc);
	check(valid_copy(to, 9, 'x'), "Duff's Device copy failed");

	memset(to, 'y', 9);

	rc = zeds_device(from, to, 9);
	check(rc == 9, "Zed's Device copy failed %d", rc);
	check(valid_copy(to, 9, 'x'), "Zed's Device copy failed");

	return 0;
error:
	return 1;
}
